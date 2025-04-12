# Espressif Projects

A collection of projects I've re/written over time for programming Espressif
MCUs. Languages used are C/C++ and MicroPython.

- For C/C++ programming I've used the ESP-IDF development tools
  v5.4.1 (https://github.com/espressif/esp-idf) on Linux Mint 22.1.
- For MicroPython I've used version 1.24.1
  (https://github.com/micropython/micropython)

These projects are current as of April 2025.

There are now three ESP-IDF folders, v4 for ESP-IDF 4.x, v5 and v5+ for ESP-IDF
v5.x. All new work is on the v5 and v5+ branches. The v4 is left for historical
purposes. The important feature on the v5/v5+ branches is the enabling of
SPIRAM on those ESP32-S3 development boards that have octal SPIRAM.

NOTE: Only ESP-IDF projects are bifurcated down the three branches. All
MicroPython projects are at this level.

Each project has a README describing in greater specific detail what it is and
what MCU and developer board it targets.

## ESP32-C3-I2C-Displays

A project derived from an ESP-IDF LED flasher example that was considerably
extended as an I2C learning laboratory.

The project still uses the RGB LED as well as six additional I2C Adafruit devices:

- a pair of LED alphanumeric displays
- a pair of LED 8x16 matrix displays
- an MCP23017 dual 8-bit port GPIO expander
- a BNO055 IMU

The project specifically targets the ESP32-C3-DevKitC-02 v1.1
(https://docs.espressif.com/projects/esp-idf/en/v4.4.2/esp32c3/hw-reference/esp32c3/user-guide-devkitc-02.html).

A key feature of this development board is its use of RISC-V executing at 160MHz
(https://riscv.org).

Note that the version under the V5 folder is now in legacy mode and is using the legacy I2C driver. The version under the V5+ folder has been migrated to use the new I2C driver. All further work will occur in the V5+ version.

## ESP32-S3-N32R8

A project with a built-in Web server that manipulates the built-in NeoPixel. It
also enbles full flash (8 MiB) and PSRAM (32 MiB). This is available in the v5+
folder. The version in the v5+ folder is a re-write of an earlier version in the
v5 folder.

_DO NOT USE THE VERSION IN THE V5 FOLDER!_

The on-board NeoPixel LED is controlled via GPIO38.

## Dual-Blink

Another project dervied from an ESP-IDF LED flasher example. Except in this
application tasking is used to control the blinking of two LEDs. The RGB LED is
in one task, and an external LED attached to pin GPIO46 is in another.

## Simple-WebServer

A project that is written in MicroPython and is meant to run with version 1.19.1
or greater. It acts as a simple access point and will present a single web page
at IP address 192.168.1.2. That web page can control the on-board RGB LED.

## WiFi-Scan

An Espressif example project that is a major re-write in C++. Part of the
main.cpp source was spun out as two files (esp_wifi_support.hpp and .cpp) to
correct the use of switch statements for converting several enumerations into
strings and begin to make it reusable. This project now compiles and runs on an
ESP32-C6-DevKitC-1 v1.1 and v1.2.

In particular the output was cleaned up to replace the crude use of tabs with
proper C/C++ print statement formatting. See the projects README file for an
output example.

## Colour_Blink

A project written explicitly for the ESP32-C6-DevKitC-1. The code simply cycles
continously through six different colours on the NeoPixel. If `idf.py` is
connected to `monitor`, then every six seconds or so a single line of text will
be emitted at the start of a colour cycle.

# Mastodon Link

<a rel="me" href="https://mastodon.cloud/@wbeebe">Mastodon</a>
