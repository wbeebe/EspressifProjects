# Wi-Fi Scan Application

This application scans for available of access points in the same area as the ESP32 developer board.

## Hardware Required

* A development board with an ESP32-S3 or ESP32-C3 SoC, such as the ESP32-S3-DevKitC-1-N8R8 or ESP32-C3-DevKitC-02.
* A USB cable for power and programming.

## How to use the Application

### Configure the Application Project
Set the correct chip target using `idf.py set-target esp32s3`.

Open the project configuration menu (`idf.py menuconfig`). 

In the `Example Configuration` menu:

* Set the Example configuration.
    * Use `Max size of scan list` to set the maximum nunber of access points to list. For this application it is set to 20.

Other configurations for this application:
* Flash is set to 8 MB
* PSRAM is enabled
* CPU Frequency is set to 240 MHz
### Build the Applicatoin and Flash the Build on the Hardware

Build the project and flash it to the board, then run the monitor tool to view
the serial output:

Run `idf.py -p PORT flash monitor` to build, flash and monitor the project.

(To exit the serial monitor, type ``Ctrl-]``.)

See the Getting Started Guide for all the steps to configure and use the ESP-IDF
to build projects.

[ESP-IDF Programming Guide Getting Started](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/index.html)

## Sample Output

When you run the application you will see the following log via the monitor 
(this is only a portion of the full output):

```
ESP-ROM:esp32s3-20210327
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
I (32) boot: compile time 08:55:22
I (32) boot: chip revision: v0.1
I (34) boot_comm: chip revision: 1, min. bootloader chip revision: 0
I (41) boot.esp32s3: Boot SPI Speed : 80MHz
I (46) boot.esp32s3: SPI Mode       : SLOW READ
I (51) boot.esp32s3: SPI Flash Size : 8MB
I (56) boot: Enabling RNG early entropy source...
I (61) boot: Partition Table:
I (65) boot: ## Label            Usage          Type ST Offset   Length
I (72) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (80) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (87) boot:  2 factory          factory app      00 00 00010000 00100000
I (95) boot: End of partition table
I (99) boot_comm: chip revision: 1, min. application chip revision: 0
I (106) esp_image: segment 0: paddr=00010020 vaddr=3c080020 size=1de74h (122484) map
I (143) esp_image: segment 1: paddr=0002de9c vaddr=3fc97400 size=0217ch (  8572) load
I (146) esp_image: segment 2: paddr=00030020 vaddr=42000020 size=75424h (480292) map
I (262) esp_image: segment 3: paddr=000a544c vaddr=3fc9957c size=02a1ch ( 10780) load
I (265) esp_image: segment 4: paddr=000a7e70 vaddr=40374000 size=13378h ( 78712) load
I (289) esp_image: segment 5: paddr=000bb1f0 vaddr=50000000 size=00010h (    16) load
I (298) boot: Loaded app from partition at offset 0x10000
I (298) boot: Disabling RNG early entropy source...
I (310) octal_psram: vendor id    : 0x0d (AP)
I (310) octal_psram: dev id       : 0x02 (generation 3)
I (310) octal_psram: density      : 0x03 (64 Mbit)
I (315) octal_psram: good-die     : 0x01 (Pass)
I (320) octal_psram: Latency      : 0x01 (Fixed)
I (325) octal_psram: VCC          : 0x00 (1.8V)
I (330) octal_psram: SRF          : 0x01 (Fast Refresh)
I (336) octal_psram: BurstType    : 0x01 (Hybrid Wrap)
I (342) octal_psram: BurstLen     : 0x01 (32 Byte)
I (348) octal_psram: Readlatency  : 0x02 (10 cycles@Fixed)
I (354) octal_psram: DriveStrength: 0x00 (1/1)
I (359) esp_psram: Found 8MB PSRAM device
I (364) esp_psram: Speed: 40MHz
I (367) cpu_start: Pro cpu up.
I (371) cpu_start: Starting app cpu, entry point is 0x40375504
0x40375504: call_start_cpu1 at /home/mint/Develop/esp/esp-idf-v5.0/components/esp_system/port/cpu_start.c:142

I (0) cpu_start: App cpu up.
I (1109) esp_psram: SPI SRAM memory test OK
I (1119) cpu_start: Pro cpu start user code
I (1119) cpu_start: cpu freq: 240000000 Hz
I (1119) cpu_start: Application information:
I (1122) cpu_start: Project name:     scan
I (1127) cpu_start: App version:      1
I (1131) cpu_start: Compile time:     Dec 15 2022 09:54:16
I (1138) cpu_start: ELF file SHA256:  adfa53cfdb2e6030...
I (1144) cpu_start: ESP-IDF:          v5.0
I (1149) heap_init: Initializing. RAM available for dynamic allocation:
I (1156) heap_init: At 3FC9FC58 len 00049AB8 (294 KiB): D/IRAM
I (1162) heap_init: At 3FCE9710 len 00005724 (21 KiB): STACK/DRAM
I (1169) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (1175) heap_init: At 600FE010 len 00001FF0 (7 KiB): RTCRAM
I (1182) esp_psram: Adding pool of 8192K of PSRAM memory to heap allocator
I (1190) spi_flash: detected chip: mxic
W (1194) spi_flash: Detected flash size > 16 MB, but access beyond 16 MB is not supported for this flash model yet.
I (1205) spi_flash: flash io: dio
W (1209) spi_flash: Detected size(32768k) larger than the size in the binary image header(8192k). Using the size in the binary image header.
I (1223) cpu_start: Starting scheduler on PRO CPU.
I (0) cpu_start: Starting scheduler on APP CPU.
I (1243) esp_psram: Reserving pool of 32K of internal memory for DMA/internal allocations
I (1253) WIFI: START ------------------
I (1253) pp: pp rom version: e7ae62f
I (1263) net80211: net80211 rom version: e7ae62f
I (1283) wifi:wifi driver task: 3fced8f0, prio:23, stack:6656, core=0
I (1283) system_api: Base MAC address is not set
I (1283) system_api: read default base MAC address from EFUSE
I (1293) wifi:wifi firmware version: 0d470ef
I (1293) wifi:wifi certification version: v7.0
I (1293) wifi:config NVS flash: enabled
I (1293) wifi:config nano formating: disabled
I (1303) wifi:Init data frame dynamic rx buffer num: 32
I (1303) wifi:Init management frame dynamic rx buffer num: 32
I (1313) wifi:Init management short buffer num: 32
I (1313) wifi:Init static tx buffer num: 16
I (1323) wifi:Init tx cache buffer num: 32
I (1323) wifi:Init static tx FG buffer num: 2
I (1333) wifi:Init static rx buffer size: 1600
I (1333) wifi:Init static rx buffer num: 10
I (1333) wifi:Init dynamic rx buffer num: 32
I (1343) wifi_init: rx ba win: 6
I (1343) wifi_init: tcpip mbox: 32
I (1343) wifi_init: udp mbox: 6
I (1353) wifi_init: tcp mbox: 6
I (1353) wifi_init: tcp tx win: 5744
I (1363) wifi_init: tcp rx win: 5744
I (1363) wifi_init: tcp mss: 1440
I (1373) wifi_init: WiFi IRAM OP enabled
I (1373) wifi_init: WiFi RX IRAM OP enabled
I (1383) phy_init: phy_version 503,13653eb,Jun  1 2022,17:47:08
W (1383) phy_init: failed to load RF calibration data (0x1102), falling back to full calibration
I (1433) wifi:mode : sta (f4:12:fa:e8:6e:78)
I (1433) wifi:enable tsf
I (3933) WIFI: SCAN RESULTS

I (3933) WIFI:            SSID: ESP32S3_5554
I (3933) WIFI:            RSSI: -9
I (3933) WIFI:         Authmod: WIFI_AUTH_OPEN
I (3933) WIFI: Pairwise Cipher: WIFI_CIPHER_TYPE_NONE
I (3943) WIFI:    Group Cipher: WIFI_CIPHER_TYPE_NONE
I (3943) WIFI:         Channel: 1

I (3953) WIFI:            SSID: g00gleeeyes
I (3953) WIFI:            RSSI: -48
I (3963) WIFI:         Authmod: WIFI_AUTH_WPA2_PSK
I (3963) WIFI: Pairwise Cipher: WIFI_CIPHER_TYPE_CCMP
I (3973) WIFI:    Group Cipher: WIFI_CIPHER_TYPE_CCMP
I (3973) WIFI:         Channel: 10

I (3983) WIFI:            SSID: SmartLife-EEFB
I (3983) WIFI:            RSSI: -71
I (3993) WIFI:         Authmod: WIFI_AUTH_OPEN
I (3993) WIFI: Pairwise Cipher: WIFI_CIPHER_TYPE_NONE
I (4003) WIFI:    Group Cipher: WIFI_CIPHER_TYPE_NONE
I (4003) WIFI:         Channel: 1

I (4013) WIFI:            SSID: Dashmeister 2.4 real
I (4013) WIFI:            RSSI: -72
I (4023) WIFI:         Authmod: WIFI_AUTH_WPA2_PSK
I (4023) WIFI: Pairwise Cipher: WIFI_CIPHER_TYPE_CCMP
I (4033) WIFI:    Group Cipher: WIFI_CIPHER_TYPE_CCMP
I (4043) WIFI:         Channel: 3
...
```