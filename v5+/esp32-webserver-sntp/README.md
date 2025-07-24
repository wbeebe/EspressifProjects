# ESP32-Webserver-SNTP
* Manipulates the Color LED using the on-board RMT for the on-board addressable LED, i.e [WS2812](http://www.world-semi.com/Certifications/WS2812B.html).
* Connects to a local WiFi access point (AP) and runs an on-chip web server. When fully operational, the IP address is printed to the terminal when `idf.py -p /dev/ttyUSB# monitor` is executed at the command line. 
* Set the board's time via external SNTP. The time is printed at the command line and is a part of the built-in webserver page.

## Hardware Used

* A specific development board with an ESP32-S3-WROOOM-2 SoC, the ESP32-S3-DevKitC-1-N32R8. This board has 8 MB PSRAM and 32 MB FLASH.
* A micro USB cable for power, programming and command line communications.
    - **Make sure the USB cable supports both data and power.**

The development board used in this application has an addressable LED:

| Board                    | LED type      | Pin      |
| ------------------------ | ------------- | -------- |
| ESP32-S3-DevKitC-1-N32R8 | Addressable   | GPIO38   |

See [Development Boards](https://www.espressif.com/en/products/devkits)
for more information about it.

## ESP-IDF Toolchain Version

This project uses ESP-IDF version 5.5 in order to enable all the flash and memory available on the ESP32-S3-DevKitC-1-N32R8.

## Configuration

Set the correct chip target using `idf.py set-target esp32s3`.

The ESP32-S3-DevKitC-1-N32R8 comes with an ESP32-S3-WROOM-2 SOC, 32 MB (N32) of flash and 8 MB (R8) of external RAM. Use `idf.py menuconfig` to configure specific properties of the DevKit board to select how much external RAM and FLASH.

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

Once configured, make sure that your local (home or work) access point SSID and password are correct and assigned to the variables EXTERNAL_AP_SSID and EXTERNAL_AP_PWD respectively in `settings.h`. Otherwise the ESP32S3 website won't be available.

The file `settings.h` will need to be created locally, as there is no version in the repo. The file `.gitignore` ignores `settings.h` so that it will never be checked into the repo. Here's a simply template to copy and paste.
```
#pragma once
#define EXTERNAL_AP_SSID "YOUR_SSID"
#define EXTERNAL_AP_PWD "YOUR_PASSWORD"
```

## Build and Flash

Run `idf.py -p PORT flash monitor` to build, flash and monitor the project.

(To exit the serial monitor, type ``Ctrl-]``.)

See the [Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) for full steps to configure and use ESP-IDF to build projects.

## Example Output

As you run the application, you'll eventually get to the section that tells
you what IP address your local WiFi router assigned to the board.

```
I (33) boot: ESP-IDF v5.5 2nd stage bootloader
I (33) boot: compile time Jul 24 2025 09:02:13
I (33) boot: Multicore bootloader
I (33) boot: chip revision: v0.1
I (36) boot: efuse block revision: v1.2
I (39) boot.esp32s3: Boot SPI Speed : 80MHz
I (43) boot.esp32s3: SPI Mode       : SLOW READ
I (47) boot.esp32s3: SPI Flash Size : 32MB
I (51) boot: Enabling RNG early entropy source...
I (56) boot: Partition Table:
I (58) boot: ## Label            Usage          Type ST Offset   Length
I (65) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (71) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (78) boot:  2 factory          factory app      00 00 00010000 00100000
I (84) boot: End of partition table
I (88) esp_image: segment 0: paddr=00010020 vaddr=3c0a0020 size=2759ch (161180) map
I (134) esp_image: segment 1: paddr=000375c4 vaddr=3fc9c500 size=051c8h ( 20936) load
I (140) esp_image: segment 2: paddr=0003c794 vaddr=40374000 size=03884h ( 14468) load
I (144) esp_image: segment 3: paddr=00040020 vaddr=42000020 size=98528h (623912) map
I (295) esp_image: segment 4: paddr=000d8550 vaddr=40377884 size=14c6ch ( 85100) load
I (319) esp_image: segment 5: paddr=000ed1c4 vaddr=600fe000 size=00020h (    32) load
I (329) boot: Loaded app from partition at offset 0x10000
I (329) boot: Disabling RNG early entropy source...
I (340) octal_psram: vendor id    : 0x0d (AP)
I (340) octal_psram: dev id       : 0x02 (generation 3)
I (340) octal_psram: density      : 0x03 (64 Mbit)
I (345) octal_psram: good-die     : 0x01 (Pass)
I (350) octal_psram: Latency      : 0x01 (Fixed)
I (356) octal_psram: VCC          : 0x00 (1.8V)
I (361) octal_psram: SRF          : 0x01 (Fast Refresh)
I (367) octal_psram: BurstType    : 0x01 (Hybrid Wrap)
I (372) octal_psram: BurstLen     : 0x01 (32 Byte)
I (378) octal_psram: Readlatency  : 0x02 (10 cycles@Fixed)
I (384) octal_psram: DriveStrength: 0x00 (1/1)
I (389) esp_psram: Found 8MB PSRAM device
I (394) esp_psram: Speed: 40MHz
I (398) cpu_start: Multicore app
I (1133) esp_psram: SPI SRAM memory test OK
I (1141) cpu_start: Pro cpu start user code
I (1142) cpu_start: cpu freq: 240000000 Hz
I (1142) app_init: Application information:
I (1145) app_init: Project name:     esp32-s3-r8n32
I (1150) app_init: App version:      e7843db-dirty
I (1156) app_init: Compile time:     Jul 24 2025 09:02:03
I (1162) app_init: ELF file SHA256:  3ab10d435a1a0a99...
I (1168) app_init: ESP-IDF:          v5.5
I (1172) efuse_init: Min chip rev:     v0.0
I (1177) efuse_init: Max chip rev:     v0.99 
I (1182) efuse_init: Chip rev:         v0.1
I (1187) heap_init: Initializing. RAM available for dynamic allocation:
I (1195) heap_init: At 3FCA5B68 len 00043BA8 (270 KiB): RAM
I (1201) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (1207) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (1213) heap_init: At 600FE020 len 00001FC8 (7 KiB): RTCRAM
I (1220) esp_psram: Adding pool of 8192K of PSRAM memory to heap allocator
I (1228) spi_flash: detected chip: mxic (opi)
I (1232) spi_flash: flash io: opi_str
I (1237) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (1244) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (1252) main_task: Started on CPU0
I (1272) esp_psram: Reserving pool of 32K of internal memory for DMA/internal allocations
I (1272) main_task: Calling app_main()
I (1272) ESP32-WEBSERVER-SNTP: APP_MAIN BEGIN
I (1282) ESP32-WEBSERVER-SNTP: CHIP_INFORMATION
I (1282) ESP32-WEBSERVER-SNTP: ESP-IDF VERSION: v5.5
I (1292) ESP32-WEBSERVER-SNTP: CHIP MODEL: ESP32S3
I (1292) ESP32-WEBSERVER-SNTP: CHIP FEATURES: WIFI BLE 
I (1302) ESP32-WEBSERVER-SNTP: REVISION: 1
I (1302) ESP32-WEBSERVER-SNTP: FREE HEAP: 8,672,192 BYTES
I (1312) ESP32-WEBSERVER-SNTP: FLASH SIZE: 33,554,432 EXTERNAL BYTES
I (1322) ESP32-WEBSERVER-SNTP: MAC ADDR: F412FAE86E78
I (1322) ESP32-WEBSERVER-SNTP: SSID: ESP32S3-6E78
I (1332) ESP32-WEBSERVER-SNTP: APP_MAIN INITIALIZE NEOPIXEL
I (1342) ESP32-WEBSERVER-SNTP: APP_MAIN CYCLE NEOPIXEL
I (4142) ESP32-WEBSERVER-SNTP: APP_MAIN INITIALISE NVS FLASH
I (4152) ESP32-WEBSERVER-SNTP: APP_MAIN INITIALIZE WIFI
I (4152) ESP32-WEBSERVER-SNTP: INITIALIZE_WIFI_STATION
I (4152) ESP32-WEBSERVER-SNTP: WIFI CREATE EVENT GROUP
I (4162) ESP32-WEBSERVER-SNTP: WIFI INITIALISE NETIF
I (4162) ESP32-WEBSERVER-SNTP: WIFI CREATE DEFAULT EVENT LOOP
I (4172) ESP32-WEBSERVER-SNTP: WIFI SET HOST NAME TO ESP32S3-6E78: SUCCESS
I (4182) ESP32-WEBSERVER-SNTP: WIFI CREATE DEFAULT WIFI STATION
I (4182) pp: pp rom version: e7ae62f
I (4192) net80211: net80211 rom version: e7ae62f
I (4202) wifi:wifi driver task: 3fceec18, prio:23, stack:6656, core=0
I (4212) wifi:wifi firmware version: f3dbad7
I (4212) wifi:wifi certification version: v7.0
I (4212) wifi:config NVS flash: enabled
I (4212) wifi:config nano formatting: disabled
I (4212) wifi:Init data frame dynamic rx buffer num: 32
I (4222) wifi:Init static rx mgmt buffer num: 5
I (4222) wifi:Init management short buffer num: 32
I (4232) wifi:Init static tx buffer num: 16
I (4232) wifi:Init static tx FG buffer num: 2
I (4242) wifi:Init static rx buffer size: 1600
I (4242) wifi:Init static rx buffer num: 10
I (4242) wifi:Init dynamic rx buffer num: 32
I (4252) wifi_init: rx ba win: 6
I (4252) wifi_init: accept mbox: 6
I (4262) wifi_init: tcpip mbox: 32
I (4262) wifi_init: udp mbox: 6
I (4262) wifi_init: tcp mbox: 6
I (4272) wifi_init: tcp tx win: 5744
I (4272) wifi_init: tcp rx win: 5744
I (4282) wifi_init: tcp mss: 1440
I (4282) wifi_init: WiFi IRAM OP enabled
I (4282) wifi_init: WiFi RX IRAM OP enabled
I (4292) ESP32-WEBSERVER-SNTP: WIFI REGISTER ESP EVENT ANY ID
I (4302) ESP32-WEBSERVER-SNTP: WIFI REGISTER IP EVENT STA GOT IP
I (4302) ESP32-WEBSERVER-SNTP: WIFI USING AP SSID: 
I (4312) ESP32-WEBSERVER-SNTP: WIFI USING AP PSWD: 
I (4322) phy_init: phy_version 701,f4f1da3a,Mar  3 2025,15:50:10
I (4352) wifi:mode : sta (f4:12:fa:e8:6e:78)
I (4352) wifi:enable tsf
I (4352) ESP32-WEBSERVER-SNTP: WIFI_EVENT_HOME_CHANNEL_CHANGE
I (4362) ESP32-WEBSERVER-SNTP: WIFI_EVENT_STA_START
I (4372) wifi:new:<7,0>, old:<1,0>, ap:<255,255>, sta:<7,0>, prof:6, snd_ch_cfg:0x0
I (4372) wifi:state: init -> auth (0xb0)
I (4372) ESP32-WEBSERVER-SNTP: WIFI_EVENT_HOME_CHANNEL_CHANGE
I (4392) wifi:state: auth -> assoc (0x0)
I (4392) wifi:state: assoc -> run (0x10)
I (4402) wifi:<ba-add>idx:0 (ifx:0, c0:06:c3:fb:71:ed), tid:5, ssn:0, winSize:64
I (4412) wifi:connected with g00gleeeyes, aid = 6, channel 7, BW20, bssid = c0:06:c3:fb:71:ed
I (4422) wifi:security: WPA2-PSK, phy: bgn, rssi: -49
I (4422) wifi:pm start, type: 1

I (4422) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (4432) wifi:set rx beacon pti, rx_bcn_pti: 0, bcn_timeout: 25000, mt_pti: 0, mt_time: 10000
I (4442) ESP32-WEBSERVER-SNTP: WIFI_EVENT_STA_CONNECTED
I (4452) wifi:<ba-add>idx:1 (ifx:0, c0:06:c3:fb:71:ed), tid:6, ssn:0, winSize:64
I (4472) wifi:AP's beacon interval = 102400 us, DTIM period = 1
I (5452) esp_netif_handlers: sta ip: 192.168.0.80, mask: 255.255.255.0, gw: 192.168.0.1
I (5452) ESP32-WEBSERVER-SNTP: IP_EVENT_STA_GOT_IP: 192.168.0.80
I (5452) ESP32-WEBSERVER-SNTP: WIFI INITIALIZE: CONNECTION SUCCESS
I (5462) ESP32-WEBSERVER-SNTP: INITIALIZE_SNTP
I (8792) wifi:<ba-del>idx:0, tid:5
I (8792) wifi:<ba-add>idx:0 (ifx:0, c0:06:c3:fb:71:ed), tid:0, ssn:0, winSize:64
I (8882) ESP32-WEBSERVER-SNTP: WIFI SUCCESSFUL INITIALIZATION
I (8882) ESP32-WEBSERVER-SNTP: APP_MAIN INITIALIZE WEBSERVER
I (8882) ESP32-WEBSERVER-SNTP: INITIALIZE_WEBSERVER
I (8892) ESP32-WEBSERVER-SNTP: WEBSERVER SUCCESSFUL STARTUP
I (8902) ESP32-WEBSERVER-SNTP: APP_MAIN ENTERING MAIN LOOP
...
```
In my case it was the line `ESP32-WEBSERVER-SNTP: IP_EVENT_STA_GOT_IP: 192.168.0.80`.
## Output Key Points
* Note that the SSID/host name is unique for each Espressif board and is based on the Espressif board on which you are running the code.

## Mobile Screenshot
This is what a typical smartphone screen would show if accessing the built-in webserver after the application starts. In this example, this is an iPhone 16 Pro Max and using the Vivaldi mobile browser.

The top of each screen will show an autogenerated SSID, built from the device ID and the last four hexadecimal digits of the devices unique ID.

The IP address at the top of each screen is the address assigned by the local access point's DHCP service. This is not fixed within the software.

![Home page](assets/ESP32S3-6E78-home.png)

Pressing any button will perform that action on the Espressif board.'Red' turns the NeoPixel on as red, 'Blue' turns the NeoPixel on as blue, etc. The 'Cycle' button cycles the NeoPixel through six distinct colors, then off. The page uses a POST action to perform the action. The page always returns to this view, only the date at the bottom updates.

The bottom of the screen shows how much free memory, how much flash total, and the time of the device. If the Espressif chip successfully sets its internal time via SNTP, then the time will show EDT. Otherwise it shows a time starting from 1 January 1970.

# Current Problem

I have uncovered a problem where after 12 hours of operation the webserver disconnects from the access point and will not reconnect. Here's a sample output captured while being monitored.
```
I (111399619) wifi:state: run -> init (0x3c0)
I (111399629) wifi:pm stop, total sleep time: 97143274297 us / 111392766110 us

I (111399629) wifi:<ba-del>idx:0, tid:0
I (111399629) wifi:<ba-del>idx:1, tid:6
I (111399629) wifi:new:<7,0>, old:<7,0>, ap:<255,255>, sta:<7,0>, prof:6, snd_ch_cfg:0x0
I (111399639) ESP32-S3-DevKitC-1.1-N32R8: WIFI_EVENT_STA_DISCONNECTED
W (111399639) httpd_txrx: httpd_sock_err: error in recv : 113
I (111399639) ESP32-S3-DevKitC-1.1-N32R8: WIFI RECONNECT ATTEMPT 1
I (111402059) ESP32-S3-DevKitC-1.1-N32R8: WIFI_EVENT_STA_DISCONNECTED
I (111402059) ESP32-S3-DevKitC-1.1-N32R8: WIFI RECONNECT ATTEMPT 2
I (111402149) wifi:new:<7,0>, old:<7,0>, ap:<255,255>, sta:<7,0>, prof:6, snd_ch_cfg:0x0
I (111402149) wifi:state: init -> auth (0xb0)
I (111402159) wifi:state: auth -> assoc (0x0)
I (111402179) wifi:state: assoc -> run (0x10)
I (111402179) wifi:state: run -> init (0x3c0)
I (111402189) wifi:new:<7,0>, old:<7,0>, ap:<255,255>, sta:<7,0>, prof:6, snd_ch_cfg:0x0
I (111402189) ESP32-S3-DevKitC-1.1-N32R8: WIFI_EVENT_STA_DISCONNECTED
I (111402189) ESP32-S3-DevKitC-1.1-N32R8: WIFI RECONNECT ATTEMPT 3
W (111402479) wifi:tx null, bss is null
I (111404599) ESP32-S3-DevKitC-1.1-N32R8: WIFI_EVENT_STA_DISCONNECTED
I (111404599) ESP32-S3-DevKitC-1.1-N32R8: WIFI RECONNECT ATTEMPT 4
I (111404709) wifi:new:<7,0>, old:<7,0>, ap:<255,255>, sta:<7,0>, prof:6, snd_ch_cfg:0x0
I (111404709) wifi:state: init -> auth (0xb0)
I (111404749) wifi:state: auth -> assoc (0x0)
I (111404749) wifi:state: assoc -> run (0x10)
I (111404759) wifi:state: run -> init (0x3c0)
I (111404759) wifi:new:<7,0>, old:<7,0>, ap:<255,255>, sta:<7,0>, prof:6, snd_ch_cfg:0x0
I (111404759) ESP32-S3-DevKitC-1.1-N32R8: WIFI_EVENT_STA_DISCONNECTED
I (111404769) ESP32-S3-DevKitC-1.1-N32R8: WIFI RECONNECT ATTEMPT 5
W (111405049) wifi:tx null, bss is null
I (111407179) ESP32-S3-DevKitC-1.1-N32R8: WIFI_EVENT_STA_DISCONNECTED
I (111407179) ESP32-S3-DevKitC-1.1-N32R8: WIFI RECONNECT ATTEMPT 6
I (111407189) wifi:new:<7,0>, old:<7,0>, ap:<255,255>, sta:<7,0>, prof:6, snd_ch_cfg:0x0
I (111407199) wifi:state: init -> auth (0xb0)
I (111407219) wifi:state: auth -> assoc (0x0)
I (111407229) wifi:state: assoc -> run (0x10)
I (111407229) wifi:state: run -> init (0x3c0)
I (111407239) wifi:new:<7,0>, old:<7,0>, ap:<255,255>, sta:<7,0>, prof:6, snd_ch_cfg:0x0
I (111407239) ESP32-S3-DevKitC-1.1-N32R8: WIFI_EVENT_STA_DISCONNECTED
I (111407239) ESP32-S3-DevKitC-1.1-N32R8: WIFI RECONNECT ATTEMPT 7
W (111407529) wifi:tx null, bss is null
I (111409649) ESP32-S3-DevKitC-1.1-N32R8: WIFI_EVENT_STA_DISCONNECTED
I (111409649) ESP32-S3-DevKitC-1.1-N32R8: WIFI RECONNECT ATTEMPT 8
I (111412059) ESP32-S3-DevKitC-1.1-N32R8: WIFI_EVENT_STA_DISCONNECTED
I (111412059) ESP32-S3-DevKitC-1.1-N32R8: WIFI RECONNECT ATTEMPT 9
I (111412069) wifi:new:<7,0>, old:<7,0>, ap:<255,255>, sta:<7,0>, prof:6, snd_ch_cfg:0x0
I (111412069) wifi:state: init -> auth (0xb0)
I (111412089) wifi:state: auth -> assoc (0x0)
I (111412099) wifi:state: assoc -> run (0x10)
I (111412099) wifi:state: run -> init (0x3c0)
I (111412099) wifi:new:<7,0>, old:<7,0>, ap:<255,255>, sta:<7,0>, prof:6, snd_ch_cfg:0x0
I (111412109) ESP32-S3-DevKitC-1.1-N32R8: WIFI_EVENT_STA_DISCONNECTED
I (111412109) ESP32-S3-DevKitC-1.1-N32R8: WIFI RECONNECT ATTEMPT 10
W (111412399) wifi:tx null, bss is null
I (111414529) ESP32-S3-DevKitC-1.1-N32R8: WIFI_EVENT_STA_DISCONNECTED
I (111414529) ESP32-S3-DevKitC-1.1-N32R8: WIFI RECONNECT FAILURE
```
The only way to get it reconnected is to reset the board. I'm working on finding the cause and a definitive solution.

I've looked online, and this problem goes back quite a few years with no satisfactory solution. I know that the problem is limited to this project. If I run a similar project using MicroPython I don't see this happening. I'm going to look in the MicroPython WiFi code section and see how they set up WiFi and manage any problems that might crop up.
# Troubleshooting
* Make sure that your local (home or work) access point SSID and password are correctly #defined by the definitions EXTERNAL_AP_SSID and EXTERNAL_AP_PWD respectively inside settings.h. 

Note that this header file is not checked in as it contains sensitive information. You'll need to create your own version of this file with the two definitions. The defautl .gitignore file ignores checking in any file by this name.

    Copyright 2025 William H. Beebe, Jr.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
