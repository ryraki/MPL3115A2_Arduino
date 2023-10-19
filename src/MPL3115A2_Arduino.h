/*
 * Copyright 2023 ryraki
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
 * @file MPL3115A2_Arduino.h
 * @brief This file is header for MPL3115A2_Arduino
 */

#ifndef _MPL3115A2_ARDUINO_H
#define _MPL3115A2_ARDUINO_H

#include <Arduino.h>
#include "mpl3115.h"
#include <I2C_device.h>

/*
 * Definition
 */
#define I2C_address (uint8_t) 0x60

typedef enum mpl3115_mode {MPL3115_barometer=0, MPL3115_altimeter=1};
typedef enum mpl3115_OSR  {MPL3115_OSR_1=0, MPL3115_OSR_2=1, MPL3115_OSR_4=2, MPL3115_OSR_8=3, MPL3115_OSR_16=4, MPL3115_OSR_32=5, MPL3115_OSR_64=6, MPL3115_OSR_128=7};
enum mpl3115_INT {MPL3115_INT2=0, MPL3115_INT1};
enum mpl3115_pressure_target {MPL3115_P=MPL3115_OUT_P_MSB, MPL3115_P_DELTA=MPL3115_OUT_P_DELTA_MSB, MPL3115_P_MIN=MPL3115_P_MIN_MSB, MPL3115_P_MAX=MPL3115_P_MAX_MSB};
enum mpl3115_temperature_target {MPL3115_T=MPL3115_OUT_T_MSB, MPL3115_T_DELTA=MPL3115_OUT_T_DELTA_MSB, MPL3115_T_MIN=MPL3115_T_MIN_MSB, MPL3115_T_MAX=MPL3115_T_MAX_MSB};

class MPL3115A2_Arduino : public I2C_device {
  public:
    mpl3115_mode mode=MPL3115_barometer;  //!< @brief Selects the mode from baromter or altimeter
    uint8_t oneshot=0;                    //!< @brief Put 1 when oneshot mode
    uint8_t oversample=MPL3115_OSR_1;     //!< @brief Selects the oversampling ratio from mpl3115_OSR enum
    
    /**
    * @brief Initialize the device with reset with several GPIO pin configuration
    * @return WHO_AM_I register value
    */
    uint8_t init();

    /**
    * @brief Initialize the device with reset
    * @param pinconfig If you wouldn't like to config the pins by this function, put false in this parameter. This parameter can be skipped.
    * @return WHO_AM_I register value
    */
    uint8_t init(bool pinconfig);


    /**
    * @brief Set interrupt function of MPL3115A2
    * @param flag Flag for interruption: Selected from "CTRL_REG4 - Bit field value definitions" in mpl3115.h
    * @param channel Sets the flag in INT1 or 2. Be selected from mpl3115_INT
    */
    void set_interrupt(uint8_t flag, mpl3115_INT channel);

    /**
    * @brief Disable interrupt function of MPL3115A2
    * @param flag Flag for disabling interruption: Selected from "CTRL_REG4 - Bit field value definitions" in mpl3115.h
    */
    void dis_interrupt(uint8_t flag);

    /**
    * @brief Start conversion
    */
    void start_conversion();

    /**
    * @brief Start conversion with settings
    * @param _mode Setting for mode parameter in this class
    * @param _oneshot Setting for oneshot parameter in this class
    * @param _oversample Setting for oversample parameter in this class    
    */
    void start_conversion(mpl3115_mode _mode, uint8_t _oneshot, uint8_t _oversample);

    /**
    * @brief Get the pressure conversion result by reading OUT_P_xxx registers. This clears interruption.
    * @return Pressure value in float
    */
    float getP();

    /**
    * @brief Get the pressure conversion result by reading OUT_P_xxx_xxx registers
    * @param target Select from mpl3115_pressure_target if you would like to read the registers other than OUT_P_xxx
    * @return Pressure value in float
    */
    float getP(mpl3115_pressure_target target);

    /**
    * @brief Get the temperature conversion result by reading OUT_T_xxx registers. This clears interruption.
    * @return Temperature value in float
    */
    float getT();

    /**
    * @brief Get the temperature conversion result by reading OUT_T_xxx_xxx registers
    * @param target Select from mpl3115_temperature_target if you would like to read the registers other than OUT_T_xxx
    * @return Temperature value in float
    */
    float getT(mpl3115_temperature_target target);

    /**
    * @brief Set default sea level (101.326kPa) for altitude calculation.
    */
    void set_sealevel();

    /**
    * @brief Set reference sea level for altitude calculation
    * @param pressure Reference sea level value in kPa unit
    */
    void set_sealevel(float pressure);

    /**
    * @brief Set threshold (target) for interruption
    * @param pressure Pressure threshold (target) for threshold interruption in kPa unit
    * @param temperature Temperature threshold (target) for threshold interruption in degC unit
    * @param pressure_window Pressure window value referring to target for window interruption in kPa unit
    * @param temperature_window Temperature window value referring to target for window interruption in degC unit
    */
    void set_threshold(float pressure, uint8_t temperature, float pressure_window, uint8_t temperature_window);

    /** Create a MPL3115A2_Arduino instance
    */    
    MPL3115A2_Arduino();

    /** Create a MPL3115A2_Arduino instance
    * @param i2c_address If the device is configured with address other than I2C_address(=0x60), put its address here.
    */
    MPL3115A2_Arduino(uint8_t i2c_address);

    /** Create a MPL3115A2_Arduino instance
    * @param wire TwoWire instance
    * @param i2c_address If the device is configured with address other than I2C_address(=0x60), put its address here.
    */
    MPL3115A2_Arduino(TwoWire& wire, uint8_t i2c_address);

    /** Destructor of MPL3115A2_Arduino
    */  
    virtual ~MPL3115A2_Arduino();

  #if DOXYGEN_ONLY
    /** Get temperature value in degree Celsius [°C] 
    *
    *	This method simply calls "temp()" method	
    *
    * @return temperature value in degree Celsius [°C] 
    */
    virtual float read( void );

    /** Ping the device
    *
    * @return true when ACK 
    */
    bool ping( void );
      
    /** Multiple register write
    * 
    * @param reg register index/address/pointer
    * @param data pointer to data buffer
    * @param size data size
    * @return transferred data size
    */
    int reg_w( uint8_t reg_adr, uint8_t *data, uint16_t size );

    /** Single register write
    * 
    * @param reg register index/address/pointer
    * @param data pointer to data buffer
    * @param size data size
    * @return transferred data size
    */
    int reg_w( uint8_t reg_adr, uint8_t data );

    /** Multiple register read
    * 
    * @param reg register index/address/pointer
    * @param data pointer to data buffer
    * @param size data size
    * @return transferred data size
    */
    int reg_r( uint8_t reg_adr, uint8_t *data, uint16_t size );

    /** Single register read
    * 
    * @param reg register index/address/pointer
    * @return read data
    */
    uint8_t	reg_r( uint8_t reg_adr );

    /** Register write, 8 bit
    *
    * @param reg register index/address/pointer
    * @param val data value
    */
    void write_r8( uint8_t reg, uint8_t val );

    /** Register write, 16 bit
    * 
    *	This 16 bit access may ot be common but it's useful for sensor devices
    *
    * @param reg register index/address/pointer
    * @param val data value
    */
    void write_r16( uint8_t reg, uint16_t val );

    /** Register read, 8 bit
    *
    * @param reg register index/address/pointer
    * @return data value
    */
    uint8_t read_r8( uint8_t reg );

    /** Register read, 16 bit
    *	
    *	This 16 bit access may ot be common but it's useful for sensor devices
    *
    * @param reg register index/address/pointer
    * @return data value
    */
    uint16_t read_r16( uint8_t reg );

    /** Register overwriting with bit-mask
    *	
    *	Register can be updated by bit level
    *
    * @param reg register index/address/pointer
    * @param mask bit-mask to protect overwriting
    * @param value value to overwrite
    */
    void bit_op8(  uint8_t reg,  uint8_t mask,  uint8_t value );
    void bit_op16( uint8_t reg, uint16_t mask, uint16_t value );
  #endif	// DOXYGEN_ONLY
};

#endif