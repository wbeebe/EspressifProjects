# I2C Multiple Sensor and Display Application
This application uses an ESP32-C3 development board and demonstrates:
* how to blink an LED using GPIO or RMT for the addressable LED,
i.e. [WS2812](http://www.world-semi.com/Certifications/WS2812B.html), and
* how to address Adafruit LED I2C displays attached via the I2C buss, and
* how to address the Adafruit BNO055 original breakout board.

## How to Use This Application
### Hardware Required

* An ESP32 development board with a RISC-V processor, such as the ESP32-C3-DevKitC-02 v1.1
* One or more Adafruit LED displays driven by the HT16K33 LED controller/driver
* One Adafruit BNO055 breakout board
* A USB cable for power and programming.

Some development boards use an addressable LED. These development boards include:

| Board                | LED type             | Pin     |
| -------------------- | -------------------- | ------- |
| ESP32-C3-DevKitC-02* | Addressable          | GPIO8   |
| ESP32-C3-DevKitM-1   | Addressable          | GPIO8   |

\*This version used.

See [Development Boards](https://www.espressif.com/en/products/devkits) for more information about it.

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

See the [Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) for full steps to configure and use ESP-IDF to build projects.

## Example Output

As you run the application you will see the LED blinking, according to the previously defined period. You will also see the LED displays displaying numeric information. Please read the source file main.cpp for further details.

For the addressable LED you can change the LED color by setting the value `pStrip_a->set_pixel(pStrip_a, 0, 16, 16, 16);` (LED Strip, Pixel Number, Red, Green, Blue) with values from 0 to 255 in the `main.cpp` file.

Note: The LED color order is red, blue, green, cyan, magenta, yellow, and black.

The pixel number indicates the pixel position in the LED strip. For a single LED, use 0.

```
ESP-ROM:esp32c3-api1-20210207
Build:Feb  7 2021
rst:0x1 (POWERON),boot:0xc (SPI_FAST_FLASH_BOOT)
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fcd5820,len:0x1738
load:0x403cc710,len:0xae8
load:0x403ce710,len:0x2e38
entry 0x403cc71a
I (30) boot: ESP-IDF v5.2-dev-1051-g17d6768e65 2nd stage bootloader
I (30) boot: compile time Jun 14 2023 16:42:05
I (31) boot: chip revision: v0.3
I (35) boot.esp32c3: SPI Speed      : 80MHz
I (40) boot.esp32c3: SPI Mode       : DIO
I (44) boot.esp32c3: SPI Flash Size : 4MB
I (49) boot: Enabling RNG early entropy source...
I (54) boot: Partition Table:
I (58) boot: ## Label            Usage          Type ST Offset   Length
I (65) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (73) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (80) boot:  2 factory          factory app      00 00 00010000 00100000
I (88) boot: End of partition table
I (92) esp_image: segment 0: paddr=00010020 vaddr=3c020020 size=0b4b0h ( 46256) map
I (108) esp_image: segment 1: paddr=0001b4d8 vaddr=3fc8ca00 size=011a8h (  4520) load
I (110) esp_image: segment 2: paddr=0001c688 vaddr=40380000 size=03990h ( 14736) load
I (120) esp_image: segment 3: paddr=00020020 vaddr=42000020 size=1baf8h (113400) map
I (144) esp_image: segment 4: paddr=0003bb20 vaddr=40383990 size=08edch ( 36572) load
I (155) boot: Loaded app from partition at offset 0x10000
I (155) boot: Disabling RNG early entropy source...
I (166) cpu_start: Unicore app
I (166) cpu_start: Pro cpu up.
I (175) cpu_start: Pro cpu start user code
I (175) cpu_start: cpu freq: 160000000 Hz
I (175) cpu_start: Application information:
I (178) cpu_start: Project name:     blink
I (183) cpu_start: App version:      92623dd-dirty
I (188) cpu_start: Compile time:     Jun 14 2023 16:41:58
I (194) cpu_start: ELF file SHA256:  61c6f6f26549587d...
I (200) cpu_start: ESP-IDF:          v5.2-dev-1051-g17d6768e65
I (207) cpu_start: Min chip rev:     v0.3
I (212) cpu_start: Max chip rev:     v0.99 
I (216) cpu_start: Chip rev:         v0.3
I (221) heap_init: Initializing. RAM available for dynamic allocation:
I (228) heap_init: At 3FC8EAA0 len 0004DC70 (311 KiB): DRAM
I (235) heap_init: At 3FCDC710 len 00002950 (10 KiB): STACK/DRAM
I (241) heap_init: At 50000010 len 00001FD8 (7 KiB): RTCRAM
I (248) spi_flash: detected chip: generic
I (252) spi_flash: flash io: dio
I (256) sleep: Configure to isolate all GPIO pins in sleep state
I (263) sleep: Enable automatic switching of GPIO sleep configuration
I (270) app_start: Starting scheduler on CPU0
I (275) main_task: Started on CPU0
I (275) main_task: Calling app_main()
I (275) ESP32-C3-I2C-DISPLAYS: BEGIN
I (285) ESP32-C3-I2C-DISPLAYS: v5.2-dev-1051-g17d6768e65
I (285) ESP32-C3-I2C-DISPLAYS: LED CONFIGURE
I (295) gpio: GPIO[8]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
I (305) ESP32-C3-I2C-DISPLAYS: I2C CONFIGURE
I (305) ESP32-C3-I2C-DISPLAYS: I2C DEVICE SCAN.
     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
00: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
20: -- -- -- -- -- -- -- -- 28 -- -- -- -- 2D -- -- 
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
50: -- -- -- 53 -- -- -- 57 -- -- -- -- -- -- -- -- 
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
70: 70 -- 72 73 -- -- -- -- -- -- -- -- -- -- -- -- 
I (3625) BNO055: CHECK TO SEE IF BNO055 COMES OUT OF SOFTWARE RESET
I (3745) ESP32-C3-I2C-DISPLAYS: BNO055 started.
I (3745) ESP32-C3-I2C-DISPLAYS: Acceleration Rev 251
I (3745) ESP32-C3-I2C-DISPLAYS: Magnitometer Rev 50
I (3745) ESP32-C3-I2C-DISPLAYS:    Gyroscope Rev 15
I (3755) ESP32-C3-I2C-DISPLAYS:           SW Rev 785
I (3755) ESP32-C3-I2C-DISPLAYS:   Bootloader Rev 21
I (3965) ESP32-C3-I2C-DISPLAYS:    System Status 05
I (3965) ESP32-C3-I2C-DISPLAYS: Self Test Result 0F
I (3965) ESP32-C3-I2C-DISPLAYS:     System Error 00
I (3965) ESP32-C3-I2C-DISPLAYS: Alphanumeric initialized.
I (10975) ESP32-C3-I2C-DISPLAYS: Alphanumeric testing finished.
I (10975) ESP32-C3-I2C-DISPLAYS: Start cycling NeoPixel colors.
```

## Troubleshooting
* If the LED isn't blinking, check the GPIO or the LED type selection in the 
`Example Configuration` menu.