# ESP32-S3-DevKitC-1-N32R8 Test Code

This application simply blinks the Color LED using the on-board RMT for the on-board addressable LED, i.e [WS2812](http://www.world-semi.com/Certifications/WS2812B.html).

## How to Use This Application

Before project configuration and build, be sure to set the correct chip target using `idf.py set-target esp32s3`.

## Hardware Required

* A specific development board with an ESP32-S3-WROOOM-2 SoC, the ESP32-S3-DevKitC-1-N32R8.
* A USB cable for power and programming

Some development boards use an addressable LED. The development board used in this application:

| Board                   | LED type      | Pin      |
| --------------------    | ------------- | -------- |
| ESP32-S3-DevKitC-1-N8R8 | Addressable   | GPIO38   |

See [Development Boards](https://www.espressif.com/en/products/devkits)
for more information about it.

## Configuration

The ESP32-S3-DevKitC-1-N32R8 comes with an ESP32-S3-WROOM-2 SOC, 32 MB (N32) of flash and 8 MB (R8) of external RAM. We’re going to configure some of the properties of the devkit to tell the software tool chain how much flash is present, and to enable the use of the external RAM. To do this we’re going to use `idf.py menuconfig`.

Set the amount of flash from the default of 2 GB to 16 GB. 
1. At the top-level of menuconfig select Serial flasher config; 
    - select Flash size (2 MB);
    - move down to 16 MB and select it, then return to the top of menuconfig.
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

As you run the application you'll see the LED blinking.

- NOTE: ESP-IDF will not enable the full 32 MB of on-board flash. If you read the output, you'll see warnings that "...access beyond 16 MB is not supported for this flash model yet."

```
Hard resetting via RTS pin...
Executing action: monitor
Running idf_monitor in directory /home/mint/Develop/esp/v5/esp32-s3-n32r8
Executing "/home/mint/.espressif/python_env/idf5.0_py3.10_env/bin/python /home/mint/Develop/esp/esp-idf-v5.0/tools/idf_monitor.py -p /dev/ttyUSB3 -b 115200 --toolchain-prefix xtensa-esp32s3-elf- --target esp32s3 /home/mint/Develop/esp/v5/esp32-s3-n32r8/build/esp32-s3-r8n32.elf -m '/home/mint/.espressif/python_env/idf5.0_py3.10_env/bin/python' '/home/mint/Develop/esp/esp-idf-v5.0/tools/idf.py' '-p' '/dev/ttyUSB3'"...
--- idf_monitor on /dev/ttyUSB3 115200 ---
--- Quit: Ctrl+] | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
e: segment 1: paddr=0001d334 vaddr=3fc92f00 size=02ce4h�ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0x1 (POWERON),boot:0x18 (SPI_FAST_FLASH_BOOT)
SPIWP:0xee
Octal Flash Mode Enabled
For OPI Flash, Use Default Flash Boot Mode
mode:SLOW_RD, clock div:1
load:0x3fce3810,len:0x167c
load:0x403c9700,len:0xbe8
load:0x403cc700,len:0x2e98
entry 0x403c9904
I (32) boot: ESP-IDF v5.0 2nd stage bootloader
I (32) boot: compile time 09:28:47
I (32) boot: chip revision: v0.1
I (34) boot_comm: chip revision: 1, min. bootloader chip revision: 0
I (41) boot.esp32s3: Boot SPI Speed : 80MHz
I (46) boot.esp32s3: SPI Mode       : SLOW READ
I (51) boot.esp32s3: SPI Flash Size : 16MB
I (56) boot: Enabling RNG early entropy source...
I (61) boot: Partition Table:
I (65) boot: ## Label            Usage          Type ST Offset   Length
I (72) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (80) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (87) boot:  2 factory          factory app      00 00 00010000 00100000
I (95) boot: End of partition table
I (99) boot_comm: chip revision: 1, min. application chip revision: 0
I (106) esp_image: segment 0: paddr=00010020 vaddr=3c020020 size=0d30ch ( 54028) map
I (127) esp_image: segment 1: paddr=0001d334 vaddr=3fc92f00 size=02ce4h ( 11492) load
I (130) esp_image: segment 2: paddr=00020020 vaddr=42000020 size=1e860h (125024) map
I (162) esp_image: segment 3: paddr=0003e888 vaddr=3fc95be4 size=004f0h (  1264) load
I (163) esp_image: segment 4: paddr=0003ed80 vaddr=40374000 size=0ee10h ( 60944) load
I (185) esp_image: segment 5: paddr=0004db98 vaddr=50000000 size=00010h (    16) load
I (191) boot: Loaded app from partition at offset 0x10000
I (191) boot: Disabling RNG early entropy source...
I (205) octal_psram: vendor id    : 0x0d (AP)
I (205) octal_psram: dev id       : 0x02 (generation 3)
I (205) octal_psram: density      : 0x03 (64 Mbit)
I (210) octal_psram: good-die     : 0x01 (Pass)
I (215) octal_psram: Latency      : 0x01 (Fixed)
I (221) octal_psram: VCC          : 0x00 (1.8V)
I (226) octal_psram: SRF          : 0x01 (Fast Refresh)
I (232) octal_psram: BurstType    : 0x01 (Hybrid Wrap)
I (238) octal_psram: BurstLen     : 0x01 (32 Byte)
I (243) octal_psram: Readlatency  : 0x02 (10 cycles@Fixed)
I (249) octal_psram: DriveStrength: 0x00 (1/1)
I (254) esp_psram: Found 8MB PSRAM device
I (259) esp_psram: Speed: 40MHz
I (263) cpu_start: Pro cpu up.
I (267) cpu_start: Starting app cpu, entry point is 0x40375448
0x40375448: call_start_cpu1 at /home/mint/Develop/esp/esp-idf-v5.0/components/esp_system/port/cpu_start.c:142

I (0) cpu_start: App cpu up.
I (1004) esp_psram: SPI SRAM memory test OK
I (1014) cpu_start: Pro cpu start user code
I (1014) cpu_start: cpu freq: 240000000 Hz
I (1014) cpu_start: Application information:
I (1018) cpu_start: Project name:     esp32-s3-r8n32
I (1023) cpu_start: App version:      1
I (1028) cpu_start: Compile time:     Dec 13 2022 09:28:41
I (1034) cpu_start: ELF file SHA256:  4cc39fd860386538...
I (1040) cpu_start: ESP-IDF:          v5.0
I (1045) heap_init: Initializing. RAM available for dynamic allocation:
I (1052) heap_init: At 3FC96B90 len 00052B80 (330 KiB): D/IRAM
I (1059) heap_init: At 3FCE9710 len 00005724 (21 KiB): STACK/DRAM
I (1065) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (1072) heap_init: At 600FE010 len 00001FF0 (7 KiB): RTCRAM
I (1078) esp_psram: Adding pool of 8192K of PSRAM memory to heap allocator
I (1087) spi_flash: detected chip: mxic
W (1090) spi_flash: Detected flash size > 16 MB, but access beyond 16 MB is not supported for this flash model yet.
I (1101) spi_flash: flash io: dio
W (1105) spi_flash: Detected size(32768k) larger than the size in the binary image header(16384k). Using the size in the binary image header.
I (1120) cpu_start: Starting scheduler on PRO CPU.
I (0) cpu_start: Starting scheduler on APP CPU.
I (1139) esp_psram: Reserving pool of 32K of internal memory for DMA/internal allocations
I (1139) ESP32-S3-DevKitC-1.1-N32R8: BEGIN
I (1149) ESP32-S3-DevKitC-1.1-N32R8: ESP-IDF VERSION v5.0
I (1149) ESP32-S3-DevKitC-1.1-N32R8: CHIP MODEL CHIP_ESP32S3
I (1159) ESP32-S3-DevKitC-1.1-N32R8: CHIP FEATURES WIFI BLE 
I (1169) ESP32-S3-DevKitC-1.1-N32R8: REVISION 1
I (1169) ESP32-S3-DevKitC-1.1-N32R8: FREE HEAP 8726608
I (1179) ESP32-S3-DevKitC-1.1-N32R8: INITIALIZE NEOPIXEL
I (1189) gpio: GPIO[38]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
I (1189) ESP32-S3-DevKitC-1.1-N32R8: ENTER MAIN LOOP 
```

## Troubleshooting

* If the LED isn't blinking, check the GPIO or the LED type selection in the `Example Configuration` menu.
