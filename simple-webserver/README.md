# Simple Webserver Application

This application is written in MicroPython, minimum version 1.19.1.

This application demonstrates how to set up a very simple webserver by
configuring the ESP32 dev board as a WiFi acess point. Once operational the
web server allows you to turn on the RGB LED as either red, green, or blue,
or to run through a color sequence once.

## How to Use This Application

### Hardware Required

* A development board with an ESP32-S3 or ESP32-C3 SoC
* A USB cable for power and programming

See [Development Boards](https://www.espressif.com/en/products/devkits)
for more information about candidate boards.

### Software Required

MicroPython V 1.19.1 or later.
- Download for ESP32-C3 devices is here: https://micropython.org/download/esp32c3/
- Download for ESP32-S3 devices is here: https://micropython.org/download/?mcu=esp32s3
Directions for how to flash a device with MicroPython is on each page. Note that
you should download the ``.bin`` file.

## Uploading This Project

The recommended tool for moving MicroPython files onto a device is Thonny 
(https://thonny.org). The Thonny website has a demo on how to use it. Save all
project files onto the MicroPython device.

## Example Output

This is the output in the Thonny shell after the MicroPython files are all
saved onto the device, and then a contro-D is typed in the shell.
```
MPY: soft reboot
esp32, esp32, 1.19.1, v1.19.1 on 2022-08-18, ESP32S3 module with ESP32S3
MicroPython-1.19.1-xtensa-IDFv4.4.1-with-newlib3.3.0
Flash size 8,388,608 bytes
Memory free 163,136 bytes.
ESP32S3_5F50
```
In this example ``ESP32S3_5F50`` is the SSID of the webserver, and is used to
connect to, and then to bring up the address at 192.168.1.2.
## Troubleshooting
* TBD
