# ESP32-S3-DevKitC-1-N32R8
* Manipulates the Color LED using the on-board RMT for the on-board addressable LED, i.e [WS2812](http://www.world-semi.com/Certifications/WS2812B.html).
* Connects to a local WiFi access point (AP) and runs an on-chip web server. When fully operational, the IP address is printed to the terminal when `idf.py monitor` is executed at the command line. 
* Connect to and get time via SNTP. The time is printed at the command line and is a part of the built-in webserver page.

## Hardware Used

* A specific development board with an ESP32-S3-WROOOM-2 SoC, the ESP32-S3-DevKitC-1-N32R32. This board has 8 MB PSRAM and 32 MB FLASH.
* A micro USB cable for power, programming and command line communications.
    - **Make sure the USB cable supports both data and power.**

The development board used in this application has an addressable LED:

| Board                    | LED type      | Pin      |
| ------------------------ | ------------- | -------- |
| ESP32-S3-DevKitC-1-N8R32 | Addressable   | GPIO38   |

See [Development Boards](https://www.espressif.com/en/products/devkits)
for more information about it.

## ESP-IDF Toolchain Version

This project uses ESP-IDF version 5.2 beta 2 in order to enable all the flash and memory available on the ESP32-S3-DevKitC-1-N8R32. This is currently identifying itself as version v5.2-beta2.

## Configuration

Set the correct chip target using `idf.py set-target esp32s3`.

The ESP32-S3-DevKitC-1-N32R32 comes with an ESP32-S3-WROOM-2 SOC, 32 MB (N32) of flash and 8 MB (R8) of external RAM. Use `idf.py menuconfig` to configure specific properties of the DevKit board to select how much external RAM and FLASH.

Set the amount of flash from the default of 2 GB to 32 GB. 
1. At the top-level of menuconfig select Serial flasher config; 
    - select Flash size (2 MB);
    - move down to 32 MB and select it, then return to the top of menuconfig.
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

**_Once configured, make sure that your local (home or work) access point SSID and password are correct and plugged into the variables EXTERNAL_AP_SSID and EXTERNAL_AP_PWD respectively at the top of wifi_tools.cpp. Otherwise the ESP32S3 website won't be available._**

## Build and Flash

Run `idf.py -p PORT flash monitor` to build, flash and monitor the project.

(To exit the serial monitor, type ``Ctrl-]``.)

See the [Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) for full steps to configure and use ESP-IDF to build projects.

## Example Output

As you run the application, you'll eventually get to the section that tells
you what IP address your local WiFi router assigned to the board.

```
ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0x1 (POWERON),boot:0x18 (SPI_FAST_FLASH_BOOT)
SPIWP:0xee
Octal Flash Mode Enabled
For OPI Flash, Use Default Flash Boot Mode
mode:SLOW_RD, clock div:1
load:0x3fce3810,len:0x17bc
load:0x403c9700,len:0x4
load:0x403c9704,len:0xdc4
load:0x403cc700,len:0x2e28
entry 0x403c9934
I (33) boot: ESP-IDF v5.2-beta2 2nd stage bootloader
I (33) boot: compile time Jan 21 2024 16:39:10
I (33) boot: Multicore bootloader
I (37) boot: chip revision: v0.1
I (41) boot.esp32s3: Boot SPI Speed : 80MHz
I (45) boot.esp32s3: SPI Mode       : SLOW READ
I (51) boot.esp32s3: SPI Flash Size : 32MB
I (55) boot: Enabling RNG early entropy source...
I (61) boot: Partition Table:
I (64) boot: ## Label            Usage          Type ST Offset   Length
I (72) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (79) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (87) boot:  2 factory          factory app      00 00 00010000 00100000
I (94) boot: End of partition table
I (98) esp_image: segment 0: paddr=00010020 vaddr=3c0a0020 size=28004h (163844) map
I (147) esp_image: segment 1: paddr=0003802c vaddr=3fc99b00 size=04a6ch ( 19052) load
I (152) esp_image: segment 2: paddr=0003caa0 vaddr=40374000 size=03578h ( 13688) load
I (156) esp_image: segment 3: paddr=00040020 vaddr=42000020 size=93c9ch (605340) map
I (308) esp_image: segment 4: paddr=000d3cc4 vaddr=40377578 size=124f0h ( 74992) load
I (339) boot: Loaded app from partition at offset 0x10000
I (339) boot: Disabling RNG early entropy source...
I (350) cpu_start: Multicore app
I (351) octal_psram: vendor id    : 0x0d (AP)
I (351) octal_psram: dev id       : 0x02 (generation 3)
I (354) octal_psram: density      : 0x03 (64 Mbit)
I (359) octal_psram: good-die     : 0x01 (Pass)
I (365) octal_psram: Latency      : 0x01 (Fixed)
I (370) octal_psram: VCC          : 0x00 (1.8V)
I (375) octal_psram: SRF          : 0x01 (Fast Refresh)
I (381) octal_psram: BurstType    : 0x01 (Hybrid Wrap)
I (387) octal_psram: BurstLen     : 0x01 (32 Byte)
I (392) octal_psram: Readlatency  : 0x02 (10 cycles@Fixed)
I (399) octal_psram: DriveStrength: 0x00 (1/1)
I (404) esp_psram: Found 8MB PSRAM device
I (408) esp_psram: Speed: 40MHz
I (1143) esp_psram: SPI SRAM memory test OK
I (1152) cpu_start: Pro cpu start user code
I (1152) cpu_start: cpu freq: 240000000 Hz
I (1152) cpu_start: Application information:
I (1156) cpu_start: Project name:     esp32-s3-r8n32
I (1161) cpu_start: App version:      e6391eb-dirty
I (1167) cpu_start: Compile time:     Jan 21 2024 16:39:01
I (1173) cpu_start: ELF file SHA256:  0b47c86989612cd3...
I (1179) cpu_start: ESP-IDF:          v5.2-beta2
I (1184) cpu_start: Min chip rev:     v0.0
I (1189) cpu_start: Max chip rev:     v0.99 
I (1194) cpu_start: Chip rev:         v0.1
I (1199) heap_init: Initializing. RAM available for dynamic allocation:
I (1206) heap_init: At 3FCA2608 len 00047108 (284 KiB): RAM
I (1212) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (1219) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (1225) heap_init: At 600FE010 len 00001FD8 (7 KiB): RTCRAM
I (1231) esp_psram: Adding pool of 8192K of PSRAM memory to heap allocator
I (1239) spi_flash: detected chip: mxic (opi)
I (1244) spi_flash: flash io: opi_str
I (1248) sleep: Configure to isolate all GPIO pins in sleep state
I (1255) sleep: Enable automatic switching of GPIO sleep configuration
I (1262) main_task: Started on CPU0
I (1272) esp_psram: Reserving pool of 32K of internal memory for DMA/internal allocations
I (1272) main_task: Calling app_main()
I (1282) ESP32-S3-DevKitC-1.1-N32R8: APP_MAIN BEGIN
I (1282) ESP32-S3-DevKitC-1.1-N32R8: ESP-IDF VERSION: v5.2-beta2
I (1292) ESP32-S3-DevKitC-1.1-N32R8: CHIP MODEL: ESP32S3
I (1302) ESP32-S3-DevKitC-1.1-N32R8: CHIP FEATURES: WIFI BLE 
I (1302) ESP32-S3-DevKitC-1.1-N32R8: REVISION: 1
I (1312) ESP32-S3-DevKitC-1.1-N32R8: FREE HEAP: 8,685,360 BYTES
I (1312) ESP32-S3-DevKitC-1.1-N32R8: FLASH SIZE: 33,554,432 EXTERNAL BYTES
I (1322) ESP32-S3-DevKitC-1.1-N32R8: MAC ADDR: F412FAE86E78
I (1332) ESP32-S3-DevKitC-1.1-N32R8: SSID: ESP32S3-6E78
I (1332) ESP32-S3-DevKitC-1.1-N32R8: APP_MAIN INITIALIZE NEOPIXEL
I (1342) gpio: GPIO[38]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
I (1352) ESP32-S3-DevKitC-1.1-N32R8: APP_MAIN CYCLE NEOPIXEL
I (4162) ESP32-S3-DevKitC-1.1-N32R8: APP_MAIN INITIALISE NVS FLASH
I (4172) ESP32-S3-DevKitC-1.1-N32R8: APP_MAIN INITIALIZE WIFI
I (4182) ESP32-S3-DevKitC-1.1-N32R8: WIFI CREATE EVENT GROUP
I (4182) ESP32-S3-DevKitC-1.1-N32R8: WIFI INITIALISE NETIF
I (4182) ESP32-S3-DevKitC-1.1-N32R8: WIFI CREATE DEFAULT EVENT LOOP
I (4192) ESP32-S3-DevKitC-1.1-N32R8: WIFI SET HOST NAME TO ESP32S3-6E78: SUCCESS
I (4202) ESP32-S3-DevKitC-1.1-N32R8: WIFI CREATE DEFAULT WIFI STATION
I (4212) pp: pp rom version: e7ae62f
I (4212) net80211: net80211 rom version: e7ae62f
I (4222) wifi:wifi driver task: 3fcb5bc0, prio:23, stack:6656, core=0
I (4232) wifi:wifi firmware version: a75e5ea
I (4232) wifi:wifi certification version: v7.0
I (4232) wifi:config NVS flash: enabled
I (4232) wifi:config nano formating: disabled
I (4242) wifi:Init data frame dynamic rx buffer num: 32
I (4242) wifi:Init static rx mgmt buffer num: 5
I (4252) wifi:Init management short buffer num: 32
I (4252) wifi:Init static tx buffer num: 16
I (4262) wifi:Init tx cache buffer num: 32
I (4262) wifi:Init static tx FG buffer num: 2
I (4262) wifi:Init static rx buffer size: 1600
I (4272) wifi:Init static rx buffer num: 10
I (4272) wifi:Init dynamic rx buffer num: 32
I (4282) wifi_init: rx ba win: 6
I (4282) wifi_init: tcpip mbox: 32
I (4282) wifi_init: udp mbox: 6
I (4292) wifi_init: tcp mbox: 6
I (4292) wifi_init: tcp tx win: 5744
I (4302) wifi_init: tcp rx win: 5744
I (4302) wifi_init: tcp mss: 1440
I (4302) wifi_init: WiFi IRAM OP enabled
I (4312) wifi_init: WiFi RX IRAM OP enabled
I (4312) ESP32-S3-DevKitC-1.1-N32R8: WIFI REGISTER ESP EVENT ANY ID
I (4322) ESP32-S3-DevKitC-1.1-N32R8: WIFI REGISTER IP EVENT STA GOT IP
I (4332) ESP32-S3-DevKitC-1.1-N32R8: WIFI USING AP SSID: g00gleeeyes
I (4342) ESP32-S3-DevKitC-1.1-N32R8: WIFI USING AP PSWD: 51538688
I (4342) phy_init: phy_version 620,ec7ec30,Sep  5 2023,13:49:13
I (4382) wifi:mode : sta (f4:12:fa:e8:6e:78)
I (4382) wifi:enable tsf
I (4382) ESP32-S3-DevKitC-1.1-N32R8: WIFI_EVENT_STA_START
I (4392) wifi:new:<2,0>, old:<1,0>, ap:<255,255>, sta:<2,0>, prof:6
I (4392) wifi:state: init -> auth (b0)
I (4402) wifi:state: auth -> assoc (0)
I (4412) wifi:state: assoc -> run (10)
I (4482) wifi:<ba-add>idx:0 (ifx:0, c0:06:c3:fb:71:ed), tid:5, ssn:0, winSize:64
I (4542) wifi:connected with g00gleeeyes, aid = 5, channel 2, BW20, bssid = c0:06:c3:fb:71:ed
I (4542) wifi:security: WPA2-PSK, phy: bgn, rssi: -47
I (4542) wifi:pm start, type: 1

I (4542) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (4552) wifi:set rx beacon pti, rx_bcn_pti: 0, bcn_timeout: 25000, mt_pti: 0, mt_time: 10000
I (4562) wifi:AP's beacon interval = 102400 us, DTIM period = 1
I (4562) ESP32-S3-DevKitC-1.1-N32R8: WIFI UNCAUGHT WIFI_EVENT 4
I (4602) wifi:<ba-add>idx:1 (ifx:0, c0:06:c3:fb:71:ed), tid:0, ssn:0, winSize:64
I (9562) esp_netif_handlers: sta ip: 192.168.0.170, mask: 255.255.255.0, gw: 192.168.0.1
I (9562) ESP32-S3-DevKitC-1.1-N32R8: IP_EVENT_STA_GOT_IP: 192.168.0.170
I (9562) ESP32-S3-DevKitC-1.1-N32R8: WIFI INITIALIZE: CONNECTION SUCCESS
I (13912) ESP32-S3-DevKitC-1.1-N32R8: WIFI SUCCESSFUL INITIALIZATION
I (13912) ESP32-S3-DevKitC-1.1-N32R8: APP_MAIN INITIALIZE WEBSERVER
I (13922) ESP32-S3-DevKitC-1.1-N32R8: WEBSERVER SUCCESSFUL STARTUP
I (13922) ESP32-S3-DevKitC-1.1-N32R8: APP_MAIN ENTERING MAIN LOOP
```
In my case it wat the line ```esp_netif_handlers: sta ip: 192.168.0.170, mask: 255.255.255.0, gw: 192.168.0.1``` in which the address after ```sta ip:``` is the IP address I input into a browser, or 
192.168.0.170.
## Output Key Points
* Note that the SSID/host name is unique for each Espressif board and is based on the Espressif board on which you are running the code.

## Screenshots from Handsets
This is what a typical smartphone screen would show if accessing the built-in webserver after the application starts. In this example, this is an iPhone 11 Pro Max and using the default Safari browser.

The top of each screen will show an autogenerated SSID, built from the device ID and the last two hexadecimal digits of the devices unique ID.

The IP address at the top of each screen is the address assigned by the local access point's DHCP service. This is not fixed within the software.

![Main page](assets/ESP32S3-6E78-main.png)

Pressing any button will perform that act on the Espressif board. Each button's action should be self-explainatory. That is, 'Red' turns the NeoPixel on as red, 'Blue; turns the NeoPixel on as blue, etc. The 'Cycle' button cycles the NeoPixel through six distinct colors, then off.

![Page after touching any button](assets/ESP32S3-6E78-home.png)

After each button is pressed, this page is displayed with a 'Home' button which when pressed returns to the top screen. This screen also shows what button/action you pressed to get here.

Note that the bottom of all screens shows how much free memory, how much flash total, and the time of the device. If the Espressif chip successfully sets its internal time via SNTP, then the time will show EDT. Otherwise it shows a time starting from 1 January 1970.

## Troubleshooting

* Make sure that your local (home or work) access point SSID and password are correct and plugged into the variables EXTERNAL_AP_SSID and EXTERNAL_AP_PWD respectively at the top of wifi_tools.cpp. Otherwise the ESP32S3 website won't be available.
