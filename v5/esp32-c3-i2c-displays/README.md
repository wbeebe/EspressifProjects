# On-board LED and I2C Display Application
This application uses and ESP32-C3 development board and demonstrates:
* how to blink an LED using GPIO or RMT for the addressable LED,
i.e. [WS2812](http://www.world-semi.com/Certifications/WS2812B.html), and
* how to address Adafruit LED I2C displays attached via the I2C buss, and
* how to address the Adafruit BNO055 original breakout board.

## How to Use This Application
### Hardware Required

* A development board with an ESP32-C3 SoC, such as the ESP-C2-DevKitC-02 v1.1
* One or more Adafruit LED displays driven by the HT16K33 LED controller/driver
* One Adafruit BNO055 breakout board
* A USB cable for power and programming.

Some development boards use an addressable LED instead of a regular one. These
development boards include:

| Board                | LED type             | Pin     |
| -------------------- | -------------------- | ------- |
| ESP32-C3-DevKitC-02* | Addressable          | GPIO8   |
| ESP32-C3-DevKitM-1   | Addressable          | GPIO8   |

\*This version used.

See [Development Boards](https://www.espressif.com/en/products/devkits) for 
more information about it.

The following physical pins are used on the ESP32-C3-DevKitC-02 V1.1 for I2C
| Physical Pin | Pin   | I2C function |
| -------------|-------|--------------|
| 5            | GPIO5 | SDA          |
| 6            | GPIO6 | SCL          |

To power all external I2C devices, pin 1 is ground and pin 2 is +5V out.

The following Adafruit components are used in this application.
| Part                          | Link                                  | I2C Address |
|-------------------------------|---------------------------------------|------|
| 9-DOF BNO055 breakout board   | https://www.adafruit.com/product/4646 | 0x28 |
| 0.54" Quad Alphanumeric - Red | https://www.adafruit.com/product/3130 | 0x70 |
| 0.8" 8x16 LED Matrix - Red    | https://www.adafruit.com/product/3152 | 0x72 |
| 0.8" 8x16 LED Matrix - Yellow | https://www.adafruit.com/product/3153 | 0x73 |

Note that the Displays and the BNO055 used in this initial development effort
are the older versions that did not have STEMMA QT/Qwiic connectors.
### Configure the Project

First set the correct chip target using `idf.py set-target esp32c3`.

Open the project configuration menu with `idf.py menuconfig`.

In the `Example Configuration` menu:

* Select the LED type in the `Blink LED type` option.
    * Use `GPIO` for regular LED blink.
    * Use `RMT` for addressable LED blink.
        * Use `RMT Channel` to select the RMT peripheral channel.
* Set the GPIO number used for the signal in the `Blink GPIO number` option.
* Set the blinking period in the `Blink period in ms` option.

### Build and Flash

Run `idf.py -p PORT flash monitor` to build, flash and monitor the project.

(To exit the serial monitor, type ``Ctrl-]``.)

See the [Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) 
for full steps to configure and use ESP-IDF to build projects.

## Example Output

As you run the application you will see the LED blinking, according to the 
previously defined period. You will also see the LED displays displaying
numeric information. Please read the source file main.cpp for further details.

For the addressable LED you can change the LED color by setting the values 
`pStrip_a->set_pixel(pStrip_a, 0, 16, 16, 16);` 
(LED Strip, Pixel Number, Red, Green, Blue) with values from 0 to 255 in the 
`main.cpp` file.

Note: The LED color order is red, blue, green, cyan, magenta, yellow, and black.

The pixel number indicates the pixel position in the LED strip. For a single 
LED, use 0.

```
ESP-ROM:esp32c3-api1-20210207
Build:Feb  7 2021
rst:0x1 (POWERON),boot:0xc (SPI_FAST_FLASH_BOOT)
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fcd5820,len:0x16d8
load:0x403cc710,len:0x96c
load:0x403ce710,len:0x2e2c
entry 0x403cc710
I (30) boot: ESP-IDF v5.0 2nd stage bootloader
I (30) boot: compile time 16:45:52
I (30) boot: chip revision: v0.3
I (32) boot.esp32c3: SPI Speed      : 80MHz
I (37) boot.esp32c3: SPI Mode       : DIO
I (41) boot.esp32c3: SPI Flash Size : 4MB
I (46) boot: Enabling RNG early entropy source...
I (52) boot: Partition Table:
I (55) boot: ## Label            Usage          Type ST Offset   Length
I (62) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (70) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (77) boot:  2 factory          factory app      00 00 00010000 00100000
I (85) boot: End of partition table
I (89) esp_image: segment 0: paddr=00010020 vaddr=3c020020 size=09ca8h ( 40104) map
I (104) esp_image: segment 1: paddr=00019cd0 vaddr=3fc8ce00 size=01550h (  5456) load
I (107) esp_image: segment 2: paddr=0001b228 vaddr=40380000 size=04df0h ( 19952) load
I (118) esp_image: segment 3: paddr=00020020 vaddr=42000020 size=19644h (104004) map
I (139) esp_image: segment 4: paddr=0003966c vaddr=40384df0 size=07e78h ( 32376) load
I (145) esp_image: segment 5: paddr=000414ec vaddr=50000010 size=00010h (    16) load
I (149) boot: Loaded app from partition at offset 0x10000
I (151) boot: Disabling RNG early entropy source...
I (168) cpu_start: Pro cpu up.
I (176) cpu_start: Pro cpu start user code
I (176) cpu_start: cpu freq: 160000000 Hz
I (176) cpu_start: Application information:
I (179) cpu_start: Project name:     blink
I (184) cpu_start: App version:      1
I (189) cpu_start: Compile time:     Dec 11 2022 16:45:44
I (195) cpu_start: ELF file SHA256:  66f920c217e8c16e...
I (201) cpu_start: ESP-IDF:          v5.0
I (205) heap_init: Initializing. RAM available for dynamic allocation:
I (213) heap_init: At 3FC8F240 len 0004D4D0 (309 KiB): DRAM
I (219) heap_init: At 3FCDC710 len 00002950 (10 KiB): STACK/DRAM
I (226) heap_init: At 50000020 len 00001FE0 (7 KiB): RTCRAM
I (233) spi_flash: detected chip: generic
I (237) spi_flash: flash io: dio
I (241) cpu_start: Starting scheduler.
I (245) ESP32-C3-I2C-DISPLAYS: BEGIN
I (245) ESP32-C3-I2C-DISPLAYS: v5.0
I (245) ESP32-C3-I2C-DISPLAYS: LED CONFIGURE
I (255) gpio: GPIO[8]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
I (265) ESP32-C3-I2C-DISPLAYS: I2C CONFIGURE
I (265) ESP32-C3-I2C-DISPLAYS: I2C DEVICE SCAN.
     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
00: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
20: -- -- -- -- -- -- -- -- TO -- -- -- -- 2D -- -- 
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
50: -- -- -- 53 -- -- -- 57 -- -- -- -- -- -- -- -- 
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
70: 70 -- 72 73 -- -- -- -- -- -- -- -- -- -- -- -- 
I (3585) BNO055: CHECK TO SEE IF BNO055 COMES OUT OF SOFTWARE RESET
I (3705) ESP32-C3-I2C-DISPLAYS: BNO055 started.
I (3705) ESP32-C3-I2C-DISPLAYS: Acceleration Rev 251
I (3705) ESP32-C3-I2C-DISPLAYS: Magnitometer Rev 50
I (3705) ESP32-C3-I2C-DISPLAYS:    Gyroscope Rev 15
I (3715) ESP32-C3-I2C-DISPLAYS:           SW Rev 785
I (3715) ESP32-C3-I2C-DISPLAYS:   Bootloader Rev 21
I (3925) ESP32-C3-I2C-DISPLAYS:    System Status 05
I (3925) ESP32-C3-I2C-DISPLAYS: Self Test Result 0F
I (3925) ESP32-C3-I2C-DISPLAYS:     System Error 00
I (3925) ESP32-C3-I2C-DISPLAYS: Alphanumeric initialized.
I (10935) ESP32-C3-I2C-DISPLAYS: Alphanumeric testing finished.
I (10935) ESP32-C3-I2C-DISPLAYS: Start cycling NeoPixel colors.
```

## Troubleshooting
* If the LED isn't blinking, check the GPIO or the LED type selection in the 
`Example Configuration` menu.