# Dual Blink Application

This application demonstrates how to blink two LEDs, one using an external GPIO and the other using the on-board RMT for the on-board addressable LED, i.e [WS2812](http://www.world-semi.com/Certifications/WS2812B.html).

## How to Use This Application

Before project configuration and build, be sure to set the correct chip target using `idf.py set-target <chip_name>`. In this application it should be `esp32s3`.

## Hardware Required

* A development board with an ESP32-S3 SoC (e.g., ESP32-S3-DevKitC-1-N8R8)
* An LED and a single 2.2K resister
    * Connect the LED and resister in series, with the resister connected to ground and the LED anode (round side of the LED) connected to GPIO46 (pin 46).
* A USB cable for power and programming

Some development boards use an addressable LED.
The development board used in this application:

| Board                   | LED type      | Pin      |
| --------------------    | ------------- | -------- |
| ESP32-S3-DevKitC-1-N8R8 | Addressable   | GPIO48   |

See [Development Boards](https://www.espressif.com/en/products/devkits)
for more information about it.

## Configuration

The ESP32-S3-DevKitC-1-N8R8 comes with an ESP32-S3-WROOM-1 SOC, 8 GB (N8) of flash and 8 GB (R8) of external RAM. We’re going to configure some of the properties of the devkit to tell the software tool chain how much flash is present, and to enable the use of the external RAM. To do this we’re going to use `idf.py menuconfig`.

Set the amount of flash from the default of 2 GB to 8 GB. 
1. At the top-level of menuconfig select Serial flasher config; 
    - select Flash size (2 MB);
    - move down to 8 MB and select it, then return to the top of menuconfig.
2. Enable the external RAM.
    - At top-level of menuconfig select Component config; 
    - scroll down and select ESP PSRAM; 
    - enable Support for external, SPI-connected RAM; 
    - move down to and select SPI RAM config;
    - select Mode (QUAD/OCT) of SPI RAM chip in use (Quad Mode PSRAM); 
    - select Octal Mode PSRAM;
    - step back one level (left arrow).
3. Move down to Initialize SPI RAM during startup and enable it;
    - move down to Run memory test on SPI RAM initialization and enable it.
4. Press ‘Q’ key and 'Y' to save these changes.

## Build and Flash

Run `idf.py -p PORT flash monitor` to build, flash and monitor the project.

(To exit the serial monitor, type ``Ctrl-]``.)

See the [Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) for full steps to configure and use ESP-IDF to build projects.

## Example Output

As you run the example, you will see the LED blinking, according to the previously defined period. For the addressable LED, you can also change the LED color by setting the `pStrip_a->set_pixel(pStrip_a, 0, 16, 16, 16);` (LED Strip, Pixel Number, Red, Green, Blue) with values from 0 to 255 in the `blink.c` file.

```
Hard resetting via RTS pin...
Executing action: monitor
Running idf_monitor in directory /home/mint/Develop/esp/dualblink_v5
Executing "/home/mint/.espressif/python_env/idf5.0_py3.10_env/bin/python /home/mint/Develop/esp/esp-idf-v5.0/tools/idf_monitor.py -p /dev/ttyUSB0 -b 115200 --toolchain-prefix xtensa-esp32s3-elf- --target esp32s3 /home/mint/Develop/esp/dualblink_v5/build/dualblink_v5.elf -m '/home/mint/.espressif/python_env/idf5.0_py3.10_env/bin/python' '/home/mint/Develop/esp/esp-idf-v5.0/tools/idf.py' '-p' '/dev/ttyUSB0'"...
--- idf_monitor on /dev/ttyUSB0 115200 ---
--- Quit: Ctrl+] | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
p_image: segment 2: paddr=0001dbb8 vaddr=40374000 size=02460h (  9312)�ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0x1 (POWERON),boot:0x8 (SPI_FAST_FLASH_BOOT)
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce3810,len:0x167c
load:0x403c9700,len:0xbe8
load:0x403cc700,len:0x2e98
entry 0x403c9904
I (25) boot: ESP-IDF v5.0 2nd stage bootloader
I (25) boot: compile time 21:49:42
I (25) boot: chip revision: v0.1
I (26) boot_comm: chip revision: 1, min. bootloader chip revision: 0
I (33) boot.esp32s3: Boot SPI Speed : 80MHz
I (38) boot.esp32s3: SPI Mode       : DIO
I (43) boot.esp32s3: SPI Flash Size : 8MB
I (48) boot: Enabling RNG early entropy source...
I (53) boot: Partition Table:
I (57) boot: ## Label            Usage          Type ST Offset   Length
I (64) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (71) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (79) boot:  2 factory          factory app      00 00 00010000 00100000
I (86) boot: End of partition table
I (91) boot_comm: chip revision: 1, min. application chip revision: 0
I (98) esp_image: segment 0: paddr=00010020 vaddr=3c020020 size=0a9b4h ( 43444) map
I (114) esp_image: segment 1: paddr=0001a9dc vaddr=3fc92d00 size=031d4h ( 12756) load
I (117) esp_image: segment 2: paddr=0001dbb8 vaddr=40374000 size=02460h (  9312) load
I (125) esp_image: segment 3: paddr=00020020 vaddr=42000020 size=1d974h (121204) map
I (153) esp_image: segment 4: paddr=0003d99c vaddr=40376460 size=0c880h ( 51328) load
I (165) esp_image: segment 5: paddr=0004a224 vaddr=50000000 size=00010h (    16) load
I (171) boot: Loaded app from partition at offset 0x10000
I (172) boot: Disabling RNG early entropy source...
I (185) octal_psram: vendor id    : 0x0d (AP)
I (185) octal_psram: dev id       : 0x02 (generation 3)
I (185) octal_psram: density      : 0x03 (64 Mbit)
I (190) octal_psram: good-die     : 0x01 (Pass)
I (195) octal_psram: Latency      : 0x01 (Fixed)
I (201) octal_psram: VCC          : 0x01 (3V)
I (206) octal_psram: SRF          : 0x01 (Fast Refresh)
I (212) octal_psram: BurstType    : 0x01 (Hybrid Wrap)
I (217) octal_psram: BurstLen     : 0x01 (32 Byte)
I (223) octal_psram: Readlatency  : 0x02 (10 cycles@Fixed)
I (229) octal_psram: DriveStrength: 0x00 (1/1)
I (234) esp_psram: Found 8MB PSRAM device
I (239) esp_psram: Speed: 40MHz
I (243) cpu_start: Pro cpu up.
I (247) cpu_start: Starting app cpu, entry point is 0x4037535c
0x4037535c: call_start_cpu1 at /home/mint/Develop/esp/esp-idf-v5.0/components/esp_system/port/cpu_start.c:142

I (0) cpu_start: App cpu up.
I (984) esp_psram: SPI SRAM memory test OK
I (993) cpu_start: Pro cpu start user code
I (993) cpu_start: cpu freq: 160000000 Hz
I (994) cpu_start: Application information:
I (996) cpu_start: Project name:     dualblink_v5
I (1002) cpu_start: App version:      1
I (1006) cpu_start: Compile time:     Dec  6 2022 21:49:36
I (1013) cpu_start: ELF file SHA256:  5c83520c39687425...
I (1019) cpu_start: ESP-IDF:          v5.0
I (1023) heap_init: Initializing. RAM available for dynamic allocation:
I (1031) heap_init: At 3FC96960 len 00052DB0 (331 KiB): D/IRAM
I (1037) heap_init: At 3FCE9710 len 00005724 (21 KiB): STACK/DRAM
I (1044) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (1050) heap_init: At 600FE010 len 00001FF0 (7 KiB): RTCRAM
I (1057) esp_psram: Adding pool of 8192K of PSRAM memory to heap allocator
I (1065) spi_flash: detected chip: generic
I (1069) spi_flash: flash io: dio
I (1074) cpu_start: Starting scheduler on PRO CPU.
I (0) cpu_start: Starting scheduler on APP CPU.
I (1094) esp_psram: Reserving pool of 32K of internal memory for DMA/internal allocations
I (1094) DUAL_BLINK_V5: BEGIN
I (1104) DUAL_BLINK_V5: ESP-IDF VERSION v5.0
I (1104) DUAL_BLINK_V5: APP_MAIN CORE 0
I (1114) DUAL_BLINK_V5: FREE HEAP 8727288
I (1114) DUAL_BLINK_V5: INITIALIZE NEOPIXEL
I (1124) gpio: GPIO[48]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
I (1134) DUAL_BLINK_V5: CREATE TASK 1
I (1134) DUAL_BLINK_V5: CREATE TASK 2
I (1134) DUAL_BLINK_V5: ENTER MAIN LOOP
I (1154) gpio: GPIO[46]| InputEn: 0| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
```

## Troubleshooting

* If the LED isn't blinking, check the GPIO or the LED type selection in the `Example Configuration` menu.
