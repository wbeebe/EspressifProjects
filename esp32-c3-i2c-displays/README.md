# LED Display Example
This example demonstrates how to blink an LED using GPIO or RMT for the
addressable LED, i.e. [WS2812](http://www.world-semi.com/Certifications/WS2812B.html).
It also shows how to address a series of Adafruit seven segment I2C displays
attached via the I2C buss.

See the RMT examples in the [RMT Peripheral](../../peripherals/rmt) for more 
information about how to use it.

## How to Use This Example

### Hardware Required

* A development board with an ESP32-C3 SoC, such as the ESP-C2-DevKitC-02 v1.1
* A USB cable for power and programming.

Some development boards use an addressable LED instead of a regular one. These
development boards include:

| Board                | LED type             | Pin                  |
| -------------------- | -------------------- | -------------------- |
| ESP32-C3-DevKitC-02  | Addressable          | GPIO8                |
| ESP32-C3-DevKitM-1   | Addressable          | GPIO8                |

See [Development Boards](https://www.espressif.com/en/products/devkits) for 
more information about it.

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

As you run the example, you will see the LED blinking, according to the 
previously defined period.
For the addressable LED, you can also change the LED color by setting the 
`pStrip_a->set_pixel(pStrip_a, 0, 16, 16, 16);` 
(LED Strip, Pixel Number, Red, Green, Blue) with values from 0 to 255 in the 
`main.cpp` file.

```
mode:DIO, clock div:1
load:0x3fcd6100,len:0x16b4
load:0x403ce000,len:0x930
load:0x403d0000,len:0x2d28
entry 0x403ce000
I (30) boot: ESP-IDF v4.4.2 2nd stage bootloader
I (30) boot: compile time 12:26:55
I (30) boot: chip revision: 3
I (32) boot.esp32c3: SPI Speed      : 80MHz
I (37) boot.esp32c3: SPI Mode       : DIO
I (41) boot.esp32c3: SPI Flash Size : 2MB
I (46) boot: Enabling RNG early entropy source...
I (51) boot: Partition Table:
I (55) boot: ## Label            Usage          Type ST Offset   Length
I (62) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (70) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (77) boot:  2 factory          factory app      00 00 00010000 00100000
I (85) boot: End of partition table
I (89) esp_image: segment 0: paddr=00010020 vaddr=3c020020 size=099c0h ( 39360) map
I (104) esp_image: segment 1: paddr=000199e8 vaddr=3fc8c600 size=01498h (  5272) load
I (107) esp_image: segment 2: paddr=0001ae88 vaddr=40380000 size=05190h ( 20880) load
I (118) esp_image: segment 3: paddr=00020020 vaddr=42000020 size=18790h (100240) map
I (138) esp_image: segment 4: paddr=000387b8 vaddr=40385190 size=072bch ( 29372) load
I (144) esp_image: segment 5: paddr=0003fa7c vaddr=50000010 size=00010h (    16) load
I (148) boot: Loaded app from partition at offset 0x10000
I (150) boot: Disabling RNG early entropy source...
I (167) cpu_start: Pro cpu up.
I (175) cpu_start: Pro cpu start user code
I (175) cpu_start: cpu freq: 160000000
I (175) cpu_start: Application information:
I (178) cpu_start: Project name:     esp32-c3-i2c-displays
I (184) cpu_start: App version:      1
I (189) cpu_start: Compile time:     Aug 15 2022 12:26:44
I (195) cpu_start: ELF file SHA256:  34711dffc7351a59...
I (201) cpu_start: ESP-IDF:          v4.4.2
I (206) heap_init: Initializing. RAM available for dynamic allocation:
I (213) heap_init: At 3FC8E9E0 len 00031620 (197 KiB): DRAM
I (219) heap_init: At 3FCC0000 len 0001F060 (124 KiB): STACK/DRAM
I (226) heap_init: At 50000020 len 00001FE0 (7 KiB): RTCRAM
I (233) spi_flash: detected chip: generic
I (237) spi_flash: flash io: dio
W (241) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (254) sleep: Configure to isolate all GPIO pins in sleep state
I (261) sleep: Enable automatic switching of GPIO sleep configuration
I (268) cpu_start: Starting scheduler.
I (272) LED_DISPLAY: Configure LED.
I (272) LED_DISPLAY: Configure I2C.
I (272) LED_DISPLAY: Scan for I2C devices.
     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
00: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
70: 70 -- 72 73 -- -- -- -- -- -- -- -- -- -- -- -- 
I (2802) LED_DISPLAY: Alphanumeric initialized.
I (9802) LED_DISPLAY: Alphanumeric testing finished.
I (9802) LED_DISPLAY: Start cycling NeoPixel colors.
```

Note: The color order is red, blue, green, cyan, magenta, yellow, and black.

The pixel number indicates the pixel position in the LED strip. For a single 
LED, use 0.

## Troubleshooting
* If the LED isn't blinking, check the GPIO or the LED type selection in the 
`Example Configuration` menu.