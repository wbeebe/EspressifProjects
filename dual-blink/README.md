# Dual Blink Application

This application demonstrates how to blink two LEDs, one using using GPIO and 
the other using RMT for the on-board addressable LED, i.e. 
[WS2812](http://www.world-semi.com/Certifications/WS2812B.html).

## How to Use This Application

Before project configuration and build, be sure to set the correct chip target 
using `idf.py set-target <chip_name>`. In this application it should be `esp32s3`.

### Hardware Required

* A development board with an ESP32-S3 SoC (e.g., ESP32-S3-DevKitC)
* An LED and a single 2.2K resister
    * Connect the LED and resister in series, with the resister connected to ground and the LED anode (round side of LED) connected to GPIO46 (pin 46).
* A USB cable for power and programming

Some development boards use an addressable LED instead of a regular one.
These development boards include:

| Board                | LED type             | Pin                  |
| -------------------- | -------------------- | -------------------- |
| ESP32-S3-DevKitC-1   | Addressable          | GPIO48               |

See [Development Boards](https://www.espressif.com/en/products/devkits)
for more information about it.

### Build and Flash

Run `idf.py -p PORT flash monitor` to build, flash and monitor the project.

(To exit the serial monitor, type ``Ctrl-]``.)

See the [Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) for full steps to configure and use ESP-IDF to build projects.

## Example Output

As you run the example, you will see the LED blinking, according to the previously defined period. For the addressable LED, you can also change the LED color by setting the `pStrip_a->set_pixel(pStrip_a, 0, 16, 16, 16);` (LED Strip, Pixel Number, Red, Green, Blue) with values from 0 to 255 in the `blink.c` file.

```
rst:0x1 (POWERON),boot:0x8 (SPI_FAST_FLASH_BOOT)
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce3808,len:0x1650
load:0x403c9700,len:0xbb8
load:0x403cc700,len:0x2f88
entry 0x403c9954
I (24) boot: ESP-IDF v4.4.2 2nd stage bootloader
I (25) boot: compile time 13:10:07
I (25) boot: chip revision: 0
I (26) boot.esp32s3: Boot SPI Speed : 80MHz
I (31) boot.esp32s3: SPI Mode       : DIO
I (36) boot.esp32s3: SPI Flash Size : 2MB
I (40) boot: Enabling RNG early entropy source...
I (46) boot: Partition Table:
I (49) boot: ## Label            Usage          Type ST Offset   Length
I (57) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (64) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (72) boot:  2 factory          factory app      00 00 00010000 00100000
I (79) boot: End of partition table
I (83) esp_image: segment 0: paddr=00010020 vaddr=3c020020 size=09a7ch ( 39548) map
I (99) esp_image: segment 1: paddr=00019aa4 vaddr=3fc91d00 size=02748h ( 10056) load
I (102) esp_image: segment 2: paddr=0001c1f4 vaddr=40374000 size=03e24h ( 15908) load
I (112) esp_image: segment 3: paddr=00020020 vaddr=42000020 size=1a47ch (107644) map
I (136) esp_image: segment 4: paddr=0003a4a4 vaddr=40377e24 size=09ed8h ( 40664) load
I (146) esp_image: segment 5: paddr=00044384 vaddr=50000000 size=00010h (    16) load
I (151) boot: Loaded app from partition at offset 0x10000
I (152) boot: Disabling RNG early entropy source...
I (166) cpu_start: Pro cpu up.
I (166) cpu_start: Starting app cpu, entry point is 0x403752bc
0x403752bc: call_start_cpu1 at /home/mint/Develop/esp/esp-idf-v4.4.2/components/esp_system/port/cpu_start.c:160

I (0) cpu_start: App cpu up.
I (180) cpu_start: Pro cpu start user code
I (180) cpu_start: cpu freq: 240000000
I (180) cpu_start: Application information:
I (183) cpu_start: Project name:     dualblink
I (188) cpu_start: App version:      b49d5cc
I (193) cpu_start: Compile time:     Aug 18 2022 13:09:59
I (199) cpu_start: ELF file SHA256:  d0fd91d0d4877a8a...
I (205) cpu_start: ESP-IDF:          v4.4.2
I (210) heap_init: Initializing. RAM available for dynamic allocation:
I (217) heap_init: At 3FC94EB8 len 0004B148 (300 KiB): D/IRAM
I (223) heap_init: At 3FCE0000 len 0000EE34 (59 KiB): STACK/DRAM
I (230) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (236) heap_init: At 600FE000 len 00002000 (8 KiB): RTCRAM
I (243) spi_flash: detected chip: generic
I (247) spi_flash: flash io: dio
W (251) spi_flash: Detected size(8192k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (265) sleep: Configure to isolate all GPIO pins in sleep state
I (271) sleep: Enable automatic switching of GPIO sleep configuration
I (278) cpu_start: Starting scheduler on PRO CPU.
I (0) cpu_start: Starting scheduler on APP CPU.
I (299) DUAL_BLINK: app_main running on core 0
I (299) DUAL_BLINK: CONFIG_BLINK_GPIO 48
I (299) DUAL_BLINK: Start Task 1
I (309) DUAL_BLINK: Start Task 2
I (329) gpio: GPIO[46]| InputEn: 0| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
```

## Troubleshooting

* If the LED isn't blinking, check the GPIO or the LED type selection in the `Example Configuration` menu.
