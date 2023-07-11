/*
 * Copyright 2023 ryraki
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "MPL3115A2_Arduino.h"
#include <Wire.h>

MPL3115A2_Arduino mpl3115a2;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);

  Serial.println(mpl3115a2.init());
  mpl3115a2.set_interrupt(MPL3115_CTRL_REG4_INT_EN_DRDY_INTENABLED, MPL3115_INT1);
  
  // Read reference baromatic pressure value
  mpl3115a2.start_conversion(MPL3115_barometer, 1, MPL3115_OSR_128);
  while (digitalRead(5));
  float pressure = mpl3115a2.getP();
  Serial.println(pressure);
  
  // Set the read reference value for sealevel
  mpl3115a2.set_sealevel(pressure);
  mpl3115a2.start_conversion(MPL3115_altimeter, 0, MPL3115_OSR_128);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (digitalRead(5));
  Serial.print(mpl3115a2.getP());
  Serial.print(" ");
  Serial.println(mpl3115a2.getT());
}
