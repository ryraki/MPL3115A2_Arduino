# MPL3115A2_Arduino
This library enables the developer to evaluate NXP MPL3115A2(S) with Arduino.

> **Note**
This library works with [`I2C_device`](https://github.com/teddokano/I2C_device_Arduino) library together. Please be sure the `I2C_device` library is imported in your environment before trying to build. 

## Datasheet and Board Information
Device Information|Datasheet|Board Information
---|---|---
[MPL3115A2S]([https://www.nxp.com/products/sensors/accelerometers/2g-4g-8g-16g-low-power-12-bit-digital-accelerometer:FXLS8961AF](https://www.nxp.com/products/sensors/pressure-sensors/barometric-pressure-15-to-150-kpa/absolute-digital-pressure-sensor-20-to-110-kpa:MPL3115A2))|[MPL3115A2S.pdf](https://www.nxp.com/docs/en/data-sheet/MPL3115A2S.pdf)|[FRDMSTBC-P3115](https://www.nxp.com/design/development-boards/freedom-development-boards/sensors/sensor-toolbox-development-platform-for-mpl3115a2-pressure-altimeter-sensor:FRDMSTBC-P3115)
[MPL3115A2]([https://www.nxp.com/products/sensors/accelerometers/2g-4g-8g-16g-low-power-12-bit-digital-accelerometer:FXLS8961AF](https://www.nxp.com/products/sensors/pressure-sensors/barometric-pressure-15-to-150-kpa/absolute-digital-pressure-sensor-20-to-110-kpa:MPL3115A2))|[MPL3115A2.pdf](https://www.nxp.com/docs/en/data-sheet/MPL3115A2.pdf)|[FRDMSTBC-P3115](https://www.nxp.com/design/development-boards/freedom-development-boards/sensors/sensor-toolbox-development-platform-for-mpl3115a2-pressure-altimeter-sensor:FRDMSTBC-P3115)

## How to use
Use Library manager pane in Arduino IDE (the books mark), put this library name (MPL3115A2_Arduino) and click INSTALL button. This library is copied to your Arduino library folder (default: &lt;Your Documents folder&gt;\Arduino\libraries).  
You can find example codes inside this library by selecting from [File]-&gt;[Examples]-&gt;[MPL3115A2_Arduino].  
Please see the documents of [docs/class_f_x_l_s89xx___arduino.html](https://ryraki.github.io/MPL3115A2_Arduino/class_m_p_l3115_a2___arduino.html) in order to get the information of all the functions.

## What are inside in this library?
### List of contents
Category|Folder|Features
---|---|---
Example|[examples/example_relative_altimeter/example_relative_altimeter.ino](examples/example_relative_altimeter/example_relative_altimeter.ino)|Example codes to get the current altimeter relative to the first-taken data
Documents|docs/&lt;All data inside the folder&gt;|The documents generated by Doxygen. Please see the link: [docs/class_m_p_l3115_a2___arduino.html](https://ryraki.github.io/MPL3115A2_Arduino/class_m_p_l3115_a2___arduino.html)
Source|[src/MPL3115A2_Arduino.cpp](src/MPL3115A2_Arduino.cpp)|The C++ file for this library.
Source|[src/MPL3115A2_Arduino.h](src/MPL3115A2_Arduino.h)|The header file for MPL3115A2_Arduino.cpp.
Source|[src/mpl3115.h](src/mpl3115.h)|The header for register definition made by NXP.
Arduino|keywords.txt|Keywords data only used for Arduino IDE 1.x.
Arduino|library.properties|Library properties used by Arduino and its Library manager.
Other|Doxyfile|For Doxygen
Other|LICENSE|License data. This is BSD 3-Clause.
Other|README.md|This file.
