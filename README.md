# Espressif Projects
A collection of projects I've re/written over time for programming Espressif MCUs. Languages used are C/C++, MicroPython and CircuitPython.

* For C/C++ programming I've used the ESP-IDF development tools v4.4.3 and v5
(https://github.com/espressif/esp-idf) on Linux Mint 21.
* For MicroPython I've used version 1.19.1 (https://github.com/micropython/micropython)
* For CircuitPython I've used version 7.3.3 (https://circuitpython.org/downloads)

These projects are current as of December 2022.

There are now two major ESP-IDF folders, v4 for ESP-IDF 4.x, and v5 for ESP-IDF v5.x. All new work is down the v5 branch. The v4 is left for historical purposes. The biggest fundamental feature on the v5 branch is the enabling of SPIRAM on those ESP32-S3 and ESP32-C3 development boards that have SPIRAM.

NOTE: Only ESP-IDF projects are bifurcated down the two branches. All MicroPython and CircuitPython projects are at this level.

Each project has a README describing in greater specific detail what it is and what MCU and developer board it targets.
## ESP32-C3-I2C-Displays
A project derived from an ESP-IDF LED flasher example that was considerably extended as an I2C learning laboratory.

The project still uses the RGB LED as well as four I2C Adafruit devices:
* an alphanumeric LED display
* a pair of LED matrix display boards
* a BNO055 IMU

The project specifically targets an ESP32-C3 development board, the ESP32-C3-DevKitC-02 v1.1 (https://docs.espressif.com/projects/esp-idf/en/v4.4.2/esp32c3/hw-reference/esp32c3/user-guide-devkitc-02.html).

A key feature of this development board is its use of RISC-V executing at 160MHz (https://riscv.org).
## ESP32-S3-N32R8
A basic blink project used to try to enble full flash and PSRAM enablement. This is available in v5 (ESP-IDF V5) only. The maximum amount of flash that can be enabled with this board and ESP-IDF V5 is 16 MB. PSRAM is enable. The on-board LED is via GPIO pin 38.
## Dual-Blink
Another project dervied from an ESP-IDF LED flasher example. Except in this application tasking is used to control the blinking of two LEDs. The RGB LED is in one task, and an external LED attached to pin GPIO46 is in another.
## Simple-WebServer
A project that is written in MicroPython and is meant to run with version 1.19.1 or greater. It acts as a simple access point and will present a single web page at IP address 192.168.1.2. That web page can control the on-board RGB LED.
## WiFi-Scan
A project that is a major re-write in C++. Part of the main.cpp source was spun out as two files (esp_wifi_support.hpp and .cpp) to correct the use of switch statements for converting several enumerations into strings and begin to make it reusable.

The output was cleaned up to replace the crude use of tabs with proper C/C++ print  statement formatting. See the projects README file for an output example.