# ESP32-S3-WEBSERVER-SNTP
* Manipulates the NeoPixel LED using the on-board RMT for the on-board addressable LED, i.e [WS2812](http://www.world-semi.com/web/index.php?topclassid=16&classid=302&lanstr=en).
* Connects to a local WiFi access point (AP) and runs an on-chip web server. When fully operational, the IP address is printed to the terminal when `idf.py -p /dev/ttyUSB# monitor` is executed at the command line. 
* Set the board's internal time via external SNTP, via WiFi. The time is printed at the command line and is a part of the built-in webserver page.

## Hardware Used

* A specific development board with an ESP32-S3-WROOOM-2 SoC, the ESP32-S3-DevKitC-1-N32R16. This board has 16 MB PSRAM and 32 MB FLASH.
* A micro USB cable for power, programming and command line communications.
    - **Make sure the USB cable supports both data and power.**

The development board used in this application has an addressable LED:

| Board                     | LED type      | Pin      |
| ------------------------- | ------------- | -------- |
| ESP32-S3-DevKitC-1-N32R16 | Addressable   | GPIO38   |

See [Development Boards](https://www.espressif.com/en/products/devkits)
for more information about it.

## ESP-IDF Toolchain Version

This project uses ESP-IDF version 5.5.5 in order to enable all the flash and memory available on the ESP32-S3-DevKitC-1-N32R16.

## Configuration

Set the correct chip target using `idf.py set-target esp32s3`.

The ESP32-S3-DevKitC-1-N32R16 comes with an ESP32-S3-WROOM-2 SOC, 32 MB (N32) of flash and 16 MB (R8) of external RAM. Use `idf.py menuconfig` to configure specific properties of the DevKit board to select how much external RAM and FLASH.

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
I (32) boot: ESP-IDF v5.5.5 2nd stage bootloader
I (32) boot: compile time Aug 10 2026 09:57:52
I (33) boot: Multicore bootloader
I (33) boot: chip revision: v0.2
I (36) boot: efuse block revision: v1.3
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
I (87) esp_image: segment 0: paddr=00010020 vaddr=3c0a0020 size=1fb08h (129800) map
I (127) esp_image: segment 1: paddr=0002fb30 vaddr=3fc9ce00 size=004e8h (  1256) load
I (128) esp_image: segment 2: paddr=00030020 vaddr=42000020 size=98e60h (626272) map
I (285) esp_image: segment 3: paddr=000c8e88 vaddr=3fc9d2e8 size=051b4h ( 20916) load
I (291) esp_image: segment 4: paddr=000ce044 vaddr=40374000 size=18d58h (101720) load
I (321) esp_image: segment 5: paddr=000e6da4 vaddr=50000000 size=00020h (    32) load
I (331) boot: Loaded app from partition at offset 0x10000
I (331) boot: Disabling RNG early entropy source...
I (342) octal_psram: vendor id    : 0x0d (AP)
I (342) octal_psram: dev id       : 0x03 (generation 4)
I (342) octal_psram: density      : 0x05 (128 Mbit)
I (344) octal_psram: good-die     : 0x01 (Pass)
I (349) octal_psram: Latency      : 0x01 (Fixed)
I (353) octal_psram: VCC          : 0x00 (1.8V)
I (357) octal_psram: SRF          : 0x01 (Fast Refresh)
I (362) octal_psram: BurstType    : 0x01 (Hybrid Wrap)
I (367) octal_psram: BurstLen     : 0x01 (32 Byte)
I (371) octal_psram: Readlatency  : 0x02 (10 cycles@Fixed)
I (377) octal_psram: DriveStrength: 0x00 (1/1)
I (381) esp_psram: Found 16MB PSRAM device
I (385) esp_psram: Speed: 40MHz
I (388) cpu_start: Multicore app
I (1852) esp_psram: SPI SRAM memory test OK
I (1860) cpu_start: GPIO 44 and 43 are used as console UART I/O pins
I (1861) cpu_start: Pro cpu start user code
I (1861) cpu_start: cpu freq: 160000000 Hz
I (1863) app_init: Application information:
I (1867) app_init: Project name:     ESP32S3-WEBSERVER-SNTP
I (1872) app_init: App version:      3bd4065-dirty
I (1877) app_init: Compile time:     Aug 10 2026 22:04:57
I (1882) app_init: ELF file SHA256:  366c7d42b...
I (1886) app_init: ESP-IDF:          v5.5.5
I (1890) efuse_init: Min chip rev:     v0.0
I (1894) efuse_init: Max chip rev:     v0.99 
I (1898) efuse_init: Chip rev:         v0.2
I (1902) heap_init: Initializing. RAM available for dynamic allocation:
I (1908) heap_init: At 3FCA69A8 len 00042D68 (267 KiB): RAM
I (1914) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (1919) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (1924) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (1930) esp_psram: Adding pool of 16384K of PSRAM memory to heap allocator
I (1937) spi_flash: detected chip: mxic (opi)
I (1940) spi_flash: flash io: opi_str
I (1944) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (1950) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (1957) main_task: Started on CPU0
I (1977) esp_psram: Reserving pool of 32K of internal memory for DMA/internal allocations
I (1977) main_task: Calling app_main()
I (1977) ESP32-S3-WEBSERVER-SNTP: APP_MAIN BEGIN
I (1987) ESP32-S3-WEBSERVER-SNTP: CHIP_INFORMATION
I (1987) ESP32-S3-WEBSERVER-SNTP: ESP-IDF VERSION: v5.5.5
I (1997) ESP32-S3-WEBSERVER-SNTP: CHIP MODEL: ESP32S3
I (1997) ESP32-S3-WEBSERVER-SNTP: CHIP FEATURES: WIFI BLE 
I (2007) ESP32-S3-WEBSERVER-SNTP: REVISION: 2
I (2007) ESP32-S3-WEBSERVER-SNTP: FREE HEAP: 17,089,031 BYTES
I (2017) ESP32-S3-WEBSERVER-SNTP: FLASH SIZE: 33,554,432 EXTERNAL BYTES
I (2017) ESP32-S3-WEBSERVER-SNTP: MAC ADDR: 90E5B1CBD710
I (2027) ESP32-S3-WEBSERVER-SNTP: SSID: ESP32S3-D710
I (2027) ESP32-S3-WEBSERVER-SNTP: APP_MAIN INITIALIZE NEOPIXEL
I (2037) ESP32-S3-WEBSERVER-SNTP: APP_MAIN CYCLE NEOPIXEL
I (5537) ESP32-S3-WEBSERVER-SNTP: APP_MAIN INITIALISE NVS FLASH
I (5547) ESP32-S3-WEBSERVER-SNTP: APP_MAIN INITIALIZE WIFI
I (5547) ESP32-S3-WEBSERVER-SNTP: INITIALIZE_WIFI_STATION
I (5547) ESP32-S3-WEBSERVER-SNTP: WIFI CREATE EVENT GROUP
I (5557) ESP32-S3-WEBSERVER-SNTP: WIFI INITIALISE NETIF
I (5557) ESP32-S3-WEBSERVER-SNTP: WIFI CREATE DEFAULT EVENT LOOP
I (5567) ESP32-S3-WEBSERVER-SNTP: WIFI SET HOST NAME TO ESP32S3-D710: SUCCESS
I (5567) ESP32-S3-WEBSERVER-SNTP: WIFI CREATE DEFAULT WIFI STATION
I (5577) pp: pp rom version: e7ae62f
I (5577) net80211: net80211 rom version: e7ae62f
I (5597) wifi:wifi driver task: 3fced8a4, prio:23, stack:6656, core=0
I (5607) wifi:wifi firmware version: b9f67df
I (5607) wifi:wifi certification version: v7.0
I (5607) wifi:config NVS flash: enabled
I (5607) wifi:config nano formatting: disabled
I (5607) wifi:Init data frame dynamic rx buffer num: 32
I (5617) wifi:Init static rx mgmt buffer num: 5
I (5617) wifi:Init management short buffer num: 32
I (5617) wifi:Init dynamic tx buffer num: 32
I (5627) wifi:Init static tx FG buffer num: 2
I (5627) wifi:Init static rx buffer size: 1600
I (5637) wifi:Init static rx buffer num: 10
I (5637) wifi:Init dynamic rx buffer num: 32
I (5637) wifi_init: rx ba win: 6
I (5647) wifi_init: accept mbox: 6
I (5647) wifi_init: tcpip mbox: 32
I (5647) wifi_init: udp mbox: 6
I (5657) wifi_init: tcp mbox: 6
I (5657) wifi_init: tcp tx win: 5760
I (5657) wifi_init: tcp rx win: 5760
I (5667) wifi_init: tcp mss: 1440
I (5667) wifi_init: WiFi IRAM OP enabled
I (5667) wifi_init: WiFi RX IRAM OP enabled
I (5677) ESP32-S3-WEBSERVER-SNTP: WIFI REGISTER ESP EVENT ANY ID
I (5677) ESP32-S3-WEBSERVER-SNTP: WIFI REGISTER IP EVENT STA GOT IP
I (5687) ESP32-S3-WEBSERVER-SNTP: WIFI USING AP SSID: g00gleeeyes
I (5687) ESP32-S3-WEBSERVER-SNTP: WIFI USING AP PSWD: 51538688
I (5697) phy_init: phy_version 712,87e8c20e,Apr 13 2026,18:51:10
I (5737) wifi:mode : sta (90:e5:b1:cb:d7:10)
I (5737) wifi:enable tsf
I (5737) ESP32-S3-WEBSERVER-SNTP: WIFI_EVENT_HOME_CHANNEL_CHANGE
I (5747) ESP32-S3-WEBSERVER-SNTP: WIFI_EVENT_STA_START
I (5757) wifi:new:<9,0>, old:<1,0>, ap:<255,255>, sta:<9,0>, prof:1, snd_ch_cfg:0x0
I (5757) wifi:state: init -> auth (0xb0)
I (5757) ESP32-S3-WEBSERVER-SNTP: WIFI_EVENT_HOME_CHANNEL_CHANGE
I (5767) wifi:state: auth -> assoc (0x0)
I (6767) wifi:state: assoc -> init (0x400)
I (6777) ESP32-S3-WEBSERVER-SNTP: WIFI_EVENT_STA_DISCONNECTED
I (6777) ESP32-S3-WEBSERVER-SNTP: WIFI RECONNECT ATTEMPT DELAY
I (16777) ESP32-S3-WEBSERVER-SNTP: WIFI RECONNECT ATTEMPT 1
I (19067) wifi:state: init -> auth (0xb0)
I (19077) wifi:state: auth -> assoc (0x0)
I (19077) wifi:state: assoc -> run (0x10)
I (19087) wifi:<ba-add>idx:0 (ifx:0, c0:06:c3:fb:71:ed), tid:5, ssn:0, winSize:64
I (19097) wifi:connected with g00gleeeyes, aid = 6, channel 9, BW20, bssid = c0:06:c3:fb:71:ed
I (19097) wifi:security: WPA2-PSK, phy: bgn, rssi: -56, cipher(pairwise:0x3, group:0x1), pmf:0
I (19097) wifi:pm start, type: 1

I (19107) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (19107) wifi:set rx beacon pti, rx_bcn_pti: 0, bcn_timeout: 25000, mt_pti: 0, mt_time: 10000
I (19117) wifi:AP's beacon interval = 102400 us, DTIM period = 1
I (19127) ESP32-S3-WEBSERVER-SNTP: WIFI_EVENT_STA_CONNECTED
I (19137) wifi:<ba-add>idx:1 (ifx:0, c0:06:c3:fb:71:ed), tid:6, ssn:0, winSize:64
I (20157) esp_netif_handlers: sta ip: 192.168.0.35, mask: 255.255.255.0, gw: 192.168.0.1
I (20157) ESP32-S3-WEBSERVER-SNTP: IP_EVENT_STA_GOT_IP: 192.168.0.35
I (20157) ESP32-S3-WEBSERVER-SNTP: WIFI INITIALIZE: CONNECTION SUCCESS
I (20157) ESP32-S3-WEBSERVER-SNTP: INITIALIZE_SNTP
I (20287) wifi:<ba-del>idx:0, tid:5
I (20287) wifi:<ba-add>idx:0 (ifx:0, c0:06:c3:fb:71:ed), tid:0, ssn:0, winSize:64
I (20537) ESP32-S3-WEBSERVER-SNTP: WIFI SUCCESSFUL INITIALIZATION
I (20547) ESP32-S3-WEBSERVER-SNTP: APP_MAIN INITIALIZE WEBSERVER
I (20547) ESP32-S3-WEBSERVER-SNTP: INITIALIZE_WEBSERVER
I (20547) ESP32-S3-WEBSERVER-SNTP: WEBSERVER SUCCESSFUL STARTUP
I (20557) ESP32-S3-WEBSERVER-SNTP: APP_MAIN ENTERING MAIN LOOP
...
```
In my case it was the line `ESP32-S3-WEBSERVER-SNTP: IP_EVENT_STA_GOT_IP: 192.168.0.35`.
## Output Key Points
* Note that the SSID/host name is unique for each Espressif board and is based on the Espressif board on which you are running the code.

## Mobile Screenshot
This is what a typical smartphone screen would show if accessing the built-in webserver after the application starts. In this example, this is an iPhone 16 Pro Max and using the Safari mobile browser.

The top of each screen will show an autogenerated SSID, built from the device processor type and the last four hexadecimal digits of the device's unique ID.

The IP address at the top of each screen is the address assigned by the local access point's DHCP service. This is not fixed within the software.

<img src="assets/ESP32S3-D710-1.PNG" style="display: block; margin: auto; width: 300px; margins: 40px;"><br />
Pressing any button will perform that action on the Espressif board. For example `Red` turns the NeoPixel on as red, `Blue` turns the NeoPixel on as blue, etc. The 'Cycle' button cycles the NeoPixel through six distinct colors, then off. The page uses a POST action to perform the action. The page always returns to this view, with the button pressed filled in and the date at the bottom updated.

<img src="assets/ESP32S3-D710-2.PNG" style="display: block; margin: auto; width: 300px; margins: 40px;"><br />
For example, this is what the webpage shows after pressing `Red`. The NeoPixel will now be red. If you press `Red` again, then the NeoPixel is turned off and the `Red` button goes to its original outline. Pressing any of the other color buttons will set the NeoPixel to that color. You don't have to press a given color button twice to turn it off.

### Mobile Screenshot Values
+ At the very top is the devices SSID. In this example, it's ESP32C5-B000. This is dynamically created from information that is integral to the board itself. It will be different on any ESP32 board this software is compiled and run on.
+ Directly beneath the `Cycle` button is the time and date that was originally synced from an external SNTP server. If the application fails to reach an SNTP server, then time starts from 1 January 1970.
+ Next, is the name of the project. This is the same as the TAG string that is defined in `common.h` and is displayed while monitoring the USB output.
+ Next is the last built date, the date the application was compiled. This is not the same date it was uploaded to the part.
+ Next is the amount of PSRAM memory free in bytes.
+ Next is the amount of FLASH memory free in bytes.
+ The last line is the version of ESP-IDF used to build the application.
# Troubleshooting
* Make sure that your local (home or work) access point SSID and password are correctly #defined by the definitions EXTERNAL_AP_SSID and EXTERNAL_AP_PWD respectively inside settings.h. 

Note that this header file is not checked in as it contains sensitive information. You'll need to create your own version of this file with the two definitions. The defautl .gitignore file ignores checking in any file by this name.

    Copyright 2026 William H. Beebe, Jr.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
