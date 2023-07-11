/*
 * Copyright 2023 ryraki
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
 * @file MPL3115A2_Arduino.cpp
 * @brief This file contains the functions for MPL3115A2 pressure sensor evaluation by Arduino
 */
 
#include <Arduino.h>
#include <Wire.h>
#include "MPL3115A2_Arduino.h"

MPL3115A2_Arduino::MPL3115A2_Arduino() : I2C_device(I2C_address) {}
MPL3115A2_Arduino::MPL3115A2_Arduino(uint8_t i2c_address) : I2C_device(i2c_address) {}
MPL3115A2_Arduino::MPL3115A2_Arduino(TwoWire& wire, uint8_t i2c_address = I2C_address) : I2C_device(wire, i2c_address) {}
MPL3115A2_Arduino::~MPL3115A2_Arduino() {}

uint8_t MPL3115A2_Arduino::init() {
  return init(true);
}

uint8_t MPL3115A2_Arduino::init(bool pinconfig) {
  if (pinconfig) {
    pinMode(SDA, INPUT);
    pinMode(SCL, INPUT);
    pinMode(2, INPUT);
    pinMode(5, INPUT);
  }
  write_r8(MPL3115_CTRL_REG1, MPL3115_CTRL_REG1_RST_EN);
  delay(1200);
  return read_r8(MPL3115_WHO_AM_I);
}

void MPL3115A2_Arduino::start_conversion() {
  start_conversion(mode, oneshot, oversample);
}

void MPL3115A2_Arduino::start_conversion(mpl3115_mode _mode, uint8_t _oneshot, uint8_t _oversample) {
  mode=_mode;
  oneshot=_oneshot;
  oversample=_oversample;
  write_r8(MPL3115_PT_DATA_CFG, 0x07); // All enable
  uint8_t ctrl_reg1 = mode<<MPL3115_CTRL_REG1_ALT_SHIFT | oversample<<MPL3115_CTRL_REG1_OS_SHIFT | oneshot<< MPL3115_CTRL_REG1_OST_SHIFT;
  write_r8(MPL3115_CTRL_REG1, ctrl_reg1);
  write_r8(MPL3115_CTRL_REG1, ctrl_reg1 | MPL3115_CTRL_REG1_SBYB_ACTIVE);
  delay(1200);
}

void MPL3115A2_Arduino::set_interrupt(uint8_t flag, mpl3115_INT channel) {
  bit_op8(MPL3115_CTRL_REG4, flag, ~flag);
  bit_op8(MPL3115_CTRL_REG5, channel?0xff:0x00, ~flag);
}

void MPL3115A2_Arduino::dis_interrupt(uint8_t flag) {
  bit_op8(MPL3115_CTRL_REG4, 0x00, ~flag);
}

float MPL3115A2_Arduino::getP() {
  return getP(MPL3115_P);
}

float MPL3115A2_Arduino::getP(mpl3115_pressure_target target) {
  uint8_t readBuffer[6];
  if (target==MPL3115_P) reg_r(0x00, readBuffer, 6);
    else reg_r(target, readBuffer+MPL3115_OUT_P_MSB, 3);
  int32_t result=((int32_t)readBuffer[1]<<12)|((int32_t)readBuffer[2]<<4)|(readBuffer[3]>>4);
  float result_real=0;
  if (mode==MPL3115_barometer)
    result_real = (float)result/4000;
  else { // altimeter
    if (result>0x7FFFF) result = -((~result + 1)&0x7FFFF);
    result_real = (float) result*0.0625;
  }
  return result_real;
}

float MPL3115A2_Arduino::getT() {
  return getT(MPL3115_T);
}

float MPL3115A2_Arduino::getT(mpl3115_temperature_target target) {
  uint8_t readBuffer[6];
  if (target==MPL3115_T) reg_r(0x00, readBuffer, 6);
    else reg_r(target, readBuffer+MPL3115_OUT_T_MSB, 2);
  reg_r(target, readBuffer, 2);
  int16_t result=((int16_t)readBuffer[4]<<4)|(readBuffer[5]>>4);
  if (result>0x07FF) result = -((~result + 1)&0x7FF);
  return (float) result*0.0625;
}

void MPL3115A2_Arduino::set_sealevel() {
  set_sealevel(101.326);
}

void MPL3115A2_Arduino::set_sealevel(float pressure) {
  uint16_t P_value = pressure*500;
  uint8_t register_list[2] = {P_value>>8, P_value};
  reg_w(MPL3115_BAR_IN_MSB, register_list, 2);
}

void MPL3115A2_Arduino::set_threshold(float pressure, uint8_t temperature, float pressure_window=0, uint8_t temperature_window=0) {
  int32_t P_target, P_window;
  if (mode==MPL3115_barometer) {
    P_target = pressure*500;
    P_window = pressure_window*500;
  }
  else { // altimeter
    P_target = pressure;
    P_window = pressure_window;
  }
  Serial.println(P_target);
  Serial.println(P_window);
  uint8_t register_list[6] = {
    P_target>>8,
    P_target,
    temperature,
    P_window>>8,
    P_window,
    temperature_window
  };
  reg_w(MPL3115_P_TGT_MSB, register_list, 6);
}