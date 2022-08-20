# Espressif Projects
A collection of projects I've hacked over time for programming Espressif MCUs.
Languages used are C/C++, MicroPython and CircuitPython.

* For C/C++ programming I've used the ESP-IDF development tools v4.4.2
(https://github.com/espressif/esp-idf) on Linux Mint 21.
* For MicroPython I've used version 1.19.1 (https://github.com/micropython/micropython)
* For CircuitPython I've used version 7.3.2 (https://circuitpython.org/downloads)

These are the current releases as of August 2022.

Each project has a README describing in greater specific detail what it is 
and what MCU and developer board it targets.
## ESP32-C3-I2C-Displays
A project derived from an ESP-IDF LED flasher example that was extended as
an I2C learning laboratory.

The project still uses the RGB LED as well as four I2C Adafruit devices:
* an alphanumeric LED display
* a pair of LED matrix display boards
* a BNO055 IMU

The project speficially targets an ESP32-C3 development board, the
ESP32-C3-DevKitC-02 v1.1
(https://docs.espressif.com/projects/esp-idf/en/v4.4.2/esp32c3/hw-reference/esp32c3/user-guide-devkitc-02.html).
A key feature of this development board is its use of RISC-V executing at
160MHz (https://riscv.org).
## Dual-Blink
Another project dervied from an ESP-IDF LED flasher example. Except in this
application tasking is used to control the blinking of two LEDs. The RGB LED
is in one task, and an external LED attached to pin GPIO46 is in another.
## Simple-WebServer
A project that is written in MicroPython and is meant to run with version
1.19.1 or greater. It acts as a simple access point and will present a single
web page at IP address 192.168.1.2. That web page can control the on-board
RGB LED.
## WiFi-Scan
A project that is a major re-write of an ESP-IDF example of the same name.
The project was re-written in C++, and part of the main.cpp source was spun
out as two files (esp_wifi_support.hpp and .cpp) to correct the use of
switch statement for converting several enumerations into strings and begin to
make it reusable.
The output was cleaned up to replace the use of tabs with proper C/C++ print 
statement formatting. See the projects README file for an output example.