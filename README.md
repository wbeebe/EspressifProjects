# Espressif Projects
A collection of projects I've hacked over time for programming Espressif MCUs.
Languages used are C/C++, MicroPython and CircuitPython.

Each project has a detailed README describing what it is, and what MCU and 
developer board it targets.
### ESP32-C3-I2C-DISPLAYS
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