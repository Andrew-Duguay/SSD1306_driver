# SSD1306_driver
Lean driver for ssd1306 OLED display

## Overview

Uses bare metal drivers entirely built from scratch. Utilizes I2C communication protocol but can easily be adapted.

## Features

- 128x64 monochrome, but adaptable to varying screen sizes via ssd1306_config
- Horizontal Addressing mode
- Full page refresh required
- Primitive drawing functions: drawPixel(), drawLine(), drawCircle(), etc.
- Commands for configuration such as invert, on/off commands, sleep/wake commands, brightness, etc.

## Hardware Requirements

- SSD1306 or 1309 driven display, not compatible with other models
- STM32 dependent, but can be adapted by changing the I2C code to match platform
- I2C pins (Vcc, gnd, sda, scl), must use pull-up resistors on sda and scl (extern or internal)
- 3.3 or 5V Vcc
