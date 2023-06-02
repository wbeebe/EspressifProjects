| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C6 | ESP32-H2 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | -------- | -------- |

# Blink Example

(See the README.md file in the upper level 'examples' directory for more information about examples.)

This example demonstrates how to blink an LED using a GPIO pin or using the [led_strip](https://components.espressif.com/component/espressif/led_strip) component for the addressable LED, i.e. [WS2812](https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf).

The `led_strip` is installed via [component manager](main/idf_component.yml).

## How to Use Example

Before project configuration and build, be sure to set the correct chip target using `idf.py set-target <chip_name>`.

### Hardware Required

* A development board with an Espressif SoC (e.g., ESP32-DevKitC, ESP-WROVER-KIT, etc.)
* A USB cable for both power and programming

Some development boards use an addressable LED instead of a regular one. These development boards include:

| Board                | LED type             | Pin                  |
| -------------------- | -------------------- | -------------------- |
| ESP32-C3-DevKitC-1   | Addressable          | GPIO8                |
| ESP32-C3-DevKitM-1   | Addressable          | GPIO8                |
| ESP32-C6-DevKitC-1   | Addressable          | GPIO8                |
| ESP32-S2-DevKitM-1   | Addressable          | GPIO18               |
| ESP32-S2-Saola-1     | Addressable          | GPIO18               |
| ESP32-S3-DevKitC-1   | Addressable          | GPIO48               |

See [Development Boards](https://www.espressif.com/en/products/devkits) for more information about it.

### Configure the Project

Open the project configuration menu (`idf.py menuconfig`).

In the `Example Configuration` menu:

* Select the LED type in the `Blink LED type` option.
  * Use `GPIO` for regular LED blink.
* Set the GPIO number used for the signal in the `Blink GPIO number` option.
* Set the blinking period in the `Blink period in ms` option.

### Build and Flash

Run `idf.py -p PORT flash monitor` to build, flash and monitor the project.

(To exit the serial monitor, type ``Ctrl-]``.)

See the [Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) for full steps to configure and use ESP-IDF to build projects.

## Example Output

As you run the example, you will see the LED blinking, according to the previously defined period. For the addressable LED, you can also change the LED color by setting the `led_strip_set_pixel(led_strip, 0, 16, 16, 16);` (LED Strip, Pixel Number, Red, Green, Blue) with values from 0 to 255 in the [source file](main/blink_example_main.c).

```text
...
--- idf_monitor on /dev/ttyUSB3 115200 ---
--- Quit: Ctrl+] | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
I (194) cpu_start: ESP-IDF:          v5.2-dev-823-g903af13e84
ESP-ROM:esp32c6-20220919
Build:Sep 19 2022
rst:0x1 (POWERON),boot:0xc (SPI_FAST_FLASH_BOOT)
SPIWP:0xee
mode:DIO, clock div:2
load:0x4086c410,len:0xd44
load:0x4086e610,len:0x2db8
load:0x40875720,len:0x181c
entry 0x4086c41a
I (23) boot: ESP-IDF v5.2-dev-823-g903af13e84 2nd stage bootloader
I (24) boot: compile time Jun  2 2023 12:51:18
I (24) boot: chip revision: v0.0
I (28) boot.esp32c6: SPI Speed      : 40MHz
I (33) boot.esp32c6: SPI Mode       : DIO
I (38) boot.esp32c6: SPI Flash Size : 8MB
I (42) boot: Enabling RNG early entropy source...
I (48) boot: Partition Table:
I (51) boot: ## Label            Usage          Type ST Offset   Length
I (59) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (66) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (73) boot:  2 factory          factory app      00 00 00010000 00100000
I (81) boot: End of partition table
I (85) esp_image: segment 0: paddr=00010020 vaddr=42020020 size=08b58h ( 35672) map
I (101) esp_image: segment 1: paddr=00018b80 vaddr=40800000 size=07498h ( 29848) load
I (109) esp_image: segment 2: paddr=00020020 vaddr=42000020 size=10b10h ( 68368) map
I (124) esp_image: segment 3: paddr=00030b38 vaddr=40807498 size=02b5ch ( 11100) load
I (127) esp_image: segment 4: paddr=0003369c vaddr=4080a000 size=01134h (  4404) load
I (133) boot: Loaded app from partition at offset 0x10000
I (136) boot: Disabling RNG early entropy source...
I (152) cpu_start: Unicore app
I (153) cpu_start: Pro cpu up.
W (163) clk: esp_perip_clk_init() has not been implemented yet
I (170) cpu_start: Pro cpu start user code
I (170) cpu_start: cpu freq: 160000000 Hz
I (170) cpu_start: Application information:
I (173) cpu_start: Project name:     blink
I (178) cpu_start: App version:      c5824d0-dirty
I (183) cpu_start: Compile time:     Jun  2 2023 12:51:09
I (189) cpu_start: ELF file SHA256:  cc8763f9e...
I (194) cpu_start: ESP-IDF:          v5.2-dev-823-g903af13e84
I (201) cpu_start: Min chip rev:     v0.0
I (206) cpu_start: Max chip rev:     v0.99 
I (210) cpu_start: Chip rev:         v0.0
I (215) heap_init: Initializing. RAM available for dynamic allocation:
I (222) heap_init: At 4080C000 len 00070610 (449 KiB): D/IRAM
I (229) heap_init: At 4087C610 len 00002F54 (11 KiB): STACK/DIRAM
I (236) heap_init: At 50000010 len 00003FF0 (15 KiB): RTCRAM
I (243) spi_flash: detected chip: generic
I (247) spi_flash: flash io: dio
I (251) sleep: Configure to isolate all GPIO pins in sleep state
I (257) sleep: Enable automatic switching of GPIO sleep configuration
I (264) coexist: coex firmware version: ebddf30
I (270) coexist: coexist rom version 5b8dcfa
I (275) app_start: Starting scheduler on CPU0
I (280) main_task: Started on CPU0
I (280) main_task: Calling app_main()
I (280) COLOUR_BLINK: Configure addressable NeoPixel.
I (290) gpio: GPIO[8]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
I (300) COLOUR_BLINK: NeoPixel cycle 1.
I (5800) COLOUR_BLINK: NeoPixel cycle 2.
I (11300) COLOUR_BLINK: NeoPixel cycle 3.
I (16800) COLOUR_BLINK: NeoPixel cycle 4.
I (22300) COLOUR_BLINK: NeoPixel cycle 5.
...
```

Note: The color order could be different according to the LED model.

The pixel number indicates the pixel position in the LED strip. For a single LED, use 0.

## Troubleshooting

* If the LED isn't blinking, check the GPIO or the LED type selection in the `Example Configuration` menu.

For any technical queries, please open an [issue](https://github.com/espressif/esp-idf/issues) on GitHub. We will get back to you soon.
