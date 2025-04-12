# I2C Multiple Sensor and Display Application
This application uses an ESP32-C3 development board and demonstrates:
* how to blink an LED using GPIO or RMT for the addressable LED,
i.e. [WS2812](http://www.world-semi.com/Certifications/WS2812B.html), and
* how to address Adafruit LED I2C displays attached via the I2C buss, and
* how to address the Adafruit BNO055 original breakout board.

The software is updated to use the new i2c driver, instead of the legacy i2c driver.
The software is built with ESP-IDF version 5.4.1.

## How to Use This Application
### Hardware Required

* The ESP32-C3-DevKitC-02 v1.1 development board
* One or more Adafruit LED displays driven by the HT16K33 LED controller/driver
* One Adafruit BNO055 breakout board
* One MCP23017 I2C GPIO Expander Breakout - STEMMA QT / Qwiic board
* A USB cable for power and programming.

Some development boards use an addressable LED. These development boards include:

| Board                | LED type             | Pin     |
| -------------------- | -------------------- | ------- |
| ESP32-C3-DevKitC-02* | Addressable          | GPIO8   |
| ESP32-C3-DevKitM-1   | Addressable          | GPIO8   |

\*This version used.

See [Development Boards](https://www.espressif.com/en/products/devkits) for more information about it.

The following physical pins are used on the ESP32-C3-DevKitC-02 V1.1 for I2C port 0:
| Physical Pin | Pin   | I2C function |
| -------------|-------|--------------|
| 5            | GPIO5 | SDA          |
| 6            | GPIO6 | SCL          |

To power all external I2C devices, pin 1 is ground and pin 2 is +5V out.

The following Adafruit components are used in this application.
| Part                          | Link                                  | I2C Address |
|-------------------------------|---------------------------------------|------|
| MCP23017 I2C GPIO Expander    | https://www.adafruit.com/product/5346 | 0x20 |
| 9-DOF BNO055 breakout board   | https://www.adafruit.com/product/4646 | 0x28 |
| 0.54" Quad Alphanumeric - Red | https://www.adafruit.com/product/3130 | 0x70 |
| 0.54" Quad Alphanumeric - Red | https://www.adafruit.com/product/3130 | 0x71 |
| 0.8" 8x16 LED Matrix - Red    | https://www.adafruit.com/product/3152 | 0x72 |
| 0.8" 8x16 LED Matrix - Yellow | https://www.adafruit.com/product/3153 | 0x73 |

Note that the Displays and the BNO055 used in this initial development effort
are the older versions that did not have STEMMA QT/Qwiic connectors. Only the
MCP23017 I2C GPIO Expander Breakout has STEMMA connectors.
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
I (285) main_task: Calling app_main()
I (285) ESP32-C3-I2C-DISPLAYS: Begin
I (285) ESP-ROM:esp32c3-api1-20210207
Build:Feb  7 2021
rst:0x1 (POWERON),boot:0xc (SPI_FAST_FLASH_BOOT)
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fcd5820,len:0x1574
load:0x403cc710,len:0xc30
load:0x403ce710,len:0x2f64
entry 0x403cc71a
I (30) boot: ESP-IDF v5.4.1 2nd stage bootloader
I (30) boot: compile time Apr  7 2025 20:43:08
I (30) boot: chip revision: v0.3
I (30) boot: efuse block revision: v1.1
I (34) boot.esp32c3: SPI Speed      : 80MHz
I (38) boot.esp32c3: SPI Mode       : DIO
I (41) boot.esp32c3: SPI Flash Size : 4MB
I (45) boot: Enabling RNG early entropy source...
I (50) boot: Partition Table:
I (52) boot: ## Label            Usage          Type ST Offset   Length
I (59) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (65) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (72) boot:  2 factory          factory app      00 00 00010000 00100000
I (78) boot: End of partition table
I (81) esp_image: segment 0: paddr=00010020 vaddr=3c020020 size=0c198h ( 49560) map
I (97) esp_image: segment 1: paddr=0001c1c0 vaddr=3fc8ce00 size=015dch (  5596) load
I (98) esp_image: segment 2: paddr=0001d7a4 vaddr=40380000 size=02874h ( 10356) load
I (106) esp_image: segment 3: paddr=00020020 vaddr=42000020 size=1de80h (122496) map
I (131) esp_image: segment 4: paddr=0003dea8 vaddr=40382874 size=0a3d0h ( 41936) load
I (139) esp_image: segment 5: paddr=00048280 vaddr=50000200 size=0001ch (    28) load
I (143) boot: Loaded app from partition at offset 0x10000
I (143) boot: Disabling RNG early entropy source...
I (156) cpu_start: Unicore app
I (164) cpu_start: Pro cpu start user code
I (165) cpu_start: cpu freq: 160000000 Hz
I (165) app_init: Application information:
I (167) app_init: Project name:     esp32-c3-i2c-displays
I (172) app_init: App version:      1
I (177) app_init: Compile time:     Apr 11 2025 21:00:47
I (183) app_init: ELF file SHA256:  f779b93ac6f2ea64...
I (188) app_init: ESP-IDF:          v5.4.1
I (193) efuse_init: Min chip rev:     v0.3
I (198) efuse_init: Max chip rev:     v1.99 
I (203) efuse_init: Chip rev:         v0.3
I (208) heap_init: Initializing. RAM available for dynamic allocation:
I (215) heap_init: At 3FC8F560 len 00030AA0 (194 KiB): RAM
I (221) heap_init: At 3FCC0000 len 0001C710 (113 KiB): Retention RAM
I (228) heap_init: At 3FCDC710 len 00002950 (10 KiB): Retention RAM
I (235) heap_init: At 5000021C len 00001DCC (7 KiB): RTCRAM
I (242) spi_flash: detected chip: generic
I (246) spi_flash: flash io: dio
I (250) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (257) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (265) main_task: Started on CPU0
I (285) main_task: Calling app_main()
I (285) ESP32-C3-I2C-DISPLAYS: Begin
I (285) ESP32-C3-I2C-DISPLAYS: v5.4.1
I (285) ESP32-C3-I2C-DISPLAYS: LED Configure
I (295) ESP32-C3-I2C-DISPLAYS: I2C Configure
I (295) ESP32-C3-I2C-DISPLAYS: I2C Device Scan.
     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
00: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
20: 20 -- -- -- -- -- -- -- 28 -- -- -- -- -- -- -- 
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
70: 70 71 72 73 -- -- -- -- -- -- -- -- -- -- -- -- 
I (3615) BNO055: CHECK TO SEE IF BNO055 COMES OUT OF SOFTWARE RESET
I (3735) ESP32-C3-I2C-DISPLAYS: BNO055 BEGIN.
I (3735) ESP32-C3-I2C-DISPLAYS: Acceleration Rev 251
I (3735) ESP32-C3-I2C-DISPLAYS: Magnitometer Rev 50
I (3735) ESP32-C3-I2C-DISPLAYS:    Gyroscope Rev 15
I (3745) ESP32-C3-I2C-DISPLAYS:           SW Rev 785
I (3745) ESP32-C3-I2C-DISPLAYS:   Bootloader Rev 21
I (3955) ESP32-C3-I2C-DISPLAYS:    System Status 05
I (3955) ESP32-C3-I2C-DISPLAYS: Self Test Result 0F
I (3955) ESP32-C3-I2C-DISPLAYS:     System Error 00
I (3955) ESP32-C3-I2C-DISPLAYS: MCP23017 Initialization SUCCESS
I (3965) ESP32-C3-I2C-DISPLAYS: MCP23017 Reset SUCCESS
I (3965) ESP32-C3-I2C-DISPLAYS: MCP23017 Test SUCCESS
I (3975) ESP32-C3-I2C-DISPLAYS: Alphanumeric Initialization SUCCESS
I (5985) ESP32-C3-I2C-DISPLAYS: Alphanumeric Display All Alphanumeric Characters
I (31985) ESP32-C3-I2C-DISPLAYS: Matrix 8x16 Show All Glyphs
I (43995) ESP32-C3-I2C-DISPLAYS: Alphanumeric Testing FINISHED
I (43995) ESP32-C3-I2C-DISPLAYS: Start cycling...
```

## Troubleshooting
* If the LED isn't blinking, check the GPIO or the LED type selection in the 
`Example Configuration` menu.
