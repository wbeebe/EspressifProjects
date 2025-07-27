# I2C Multiple Sensor and Display Application
This application uses an ESP32-C3 development board and demonstrates:
* how to blink an LED using GPIO or RMT for the addressable LED,
i.e. [WS2812](http://www.world-semi.com/Certifications/WS2812B.html), and
* how to address Adafruit LED I2C displays attached via the I2C buss, and
* how to address the Adafruit BNO055 original breakout board.

The software is updated to use the new Espressif i2c driver, instead of the legacy i2c driver.
The software is built with ESP-IDF version 5.5.

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
I (30) boot: ESP-IDF v5.5 2nd stage bootloader
I (30) boot: compile time Jul 24 2025 15:44:21
I (30) boot: chip revision: v0.3
I (30) boot: efuse block revision: v1.1
I (34) boot.esp32c3: SPI Speed      : 80MHz
I (38) boot.esp32c3: SPI Mode       : DIO
I (41) boot.esp32c3: SPI Flash Size : 4MB
I (45) boot: Enabling RNG early entropy source...
I (50) boot: Partition Table:
I (52) boot: ## Label            Usage          Type ST Offset   Length
I (58) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (65) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (72) boot:  2 factory          factory app      00 00 00010000 00100000
I (78) boot: End of partition table
I (81) esp_image: segment 0: paddr=00010020 vaddr=3c030020 size=0c828h ( 51240) map
I (97) esp_image: segment 1: paddr=0001c850 vaddr=3fc8d200 size=016c8h (  5832) load
I (98) esp_image: segment 2: paddr=0001df20 vaddr=40380000 size=020f8h (  8440) load
I (105) esp_image: segment 3: paddr=00020020 vaddr=42000020 size=20b38h (133944) map
I (132) esp_image: segment 4: paddr=00040b60 vaddr=403820f8 size=0afbch ( 44988) load
I (141) esp_image: segment 5: paddr=0004bb24 vaddr=50000000 size=00020h (    32) load
I (145) boot: Loaded app from partition at offset 0x10000
I (145) boot: Disabling RNG early entropy source...
I (158) cpu_start: Unicore app
I (167) cpu_start: Pro cpu start user code
I (167) cpu_start: cpu freq: 160000000 Hz
I (167) app_init: Application information:
I (170) app_init: Project name:     esp32-c3-i2c-displays
I (176) app_init: App version:      b8040fc-dirty
I (181) app_init: Compile time:     Jul 24 2025 15:44:10
I (187) app_init: ELF file SHA256:  61bbf42f7eff05ca...
I (193) app_init: ESP-IDF:          v5.5
I (198) efuse_init: Min chip rev:     v0.3
I (202) efuse_init: Max chip rev:     v1.99 
I (207) efuse_init: Chip rev:         v0.3
I (212) heap_init: Initializing. RAM available for dynamic allocation:
I (220) heap_init: At 3FC8FA60 len 000305A0 (193 KiB): RAM
I (226) heap_init: At 3FCC0000 len 0001C710 (113 KiB): Retention RAM
I (233) heap_init: At 3FCDC710 len 00002950 (10 KiB): Retention RAM
I (240) heap_init: At 50000020 len 00001FC8 (7 KiB): RTCRAM
I (247) spi_flash: detected chip: generic
I (250) spi_flash: flash io: dio
I (255) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (262) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (269) main_task: Started on CPU0
I (289) main_task: Calling app_main()
I (289) ESP32-I2C-DEVICES: Begin
I (289) ESP32-I2C-DEVICES: v5.5
I (289) ESP32-I2C-DEVICES: LED Configure
I (299) ESP32-I2C-DEVICES: I2C Configure
I (299) ESP32-I2C-DEVICES: I2C Device Scan.
     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
00: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
20: 20 -- -- -- -- -- -- -- 28 -- -- -- -- -- -- -- 
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
70: 70 71 72 73 -- -- -- -- -- -- -- -- -- -- -- -- 
I (3619) BNO055: CHECK TO SEE IF BNO055 COMES OUT OF SOFTWARE RESET
I (3739) ESP32-I2C-DEVICES: BNO055 BEGIN
I (3739) ESP32-I2C-DEVICES: Acceleration Rev 251
I (3739) ESP32-I2C-DEVICES: Magnitometer Rev 50
I (3739) ESP32-I2C-DEVICES:    Gyroscope Rev 15
I (3739) ESP32-I2C-DEVICES:           SW Rev 785
I (3749) ESP32-I2C-DEVICES:   Bootloader Rev 21
I (3959) ESP32-I2C-DEVICES:    System Status 05
I (3959) ESP32-I2C-DEVICES: Self Test Result 0F
I (3959) ESP32-I2C-DEVICES:     System Error 00
I (3959) ESP32-I2C-DEVICES: Test Temperature 24
I (3969) ESP32-I2C-DEVICES: MCP23017 Initialization SUCCESS
I (3969) ESP32-I2C-DEVICES: MCP23017 Reset SUCCESS
I (3979) ESP32-I2C-DEVICES: MCP23017 Test SUCCESS
I (3989) ESP32-I2C-DEVICES: Alphanumeric Initialization SUCCESS
I (5999) ESP32-I2C-DEVICES: Alphanumeric Display All Alphanumeric Characters
I (31999) ESP32-I2C-DEVICES: Matrix 8x16 Show All Glyphs
I (44009) ESP32-I2C-DEVICES: Alphanumeric Testing FINISHED
I (44009) ESP32-I2C-DEVICES: Start cycling...
```

## Troubleshooting
* If the LED isn't blinking, check the GPIO or the LED type selection in the 
`Example Configuration` menu.
