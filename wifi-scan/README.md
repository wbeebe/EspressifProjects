# Wi-Fi Scan Application

This application shows how to scan for available of access points in the same
area as the ESP32 developer board.

## Hardware Required

* A development board with an ESP32-S3 or ESP32-C3 SoC, such as the ESP32-S3-DevKitC-1-N#R# or ESP32-C3-DevKitC-02.
* A USB cable for power and programming.

## How to use the Application

### Configure the Application Project
Set the correct chip target using `idf.py set-target <chip_name>`.

Open the project configuration menu (`idf.py menuconfig`). 

In the `Example Configuration` menu:

* Set the Example configuration.
    * Use `Max size of scan list` to set the maximum nunber of access points to list.

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
...
I (380) WIFI SCAN: START ------------------
I (380) pp: pp rom version: e7ae62f
I (380) net80211: net80211 rom version: e7ae62f
I (390) wifi:wifi driver task: 3fce5998, prio:23, stack:6656, core=0
I (390) system_api: Base MAC address is not set
I (390) system_api: read default base MAC address from EFUSE
I (400) wifi:wifi firmware version: eeaa27d
I (400) wifi:wifi certification version: v7.0
I (410) wifi:config NVS flash: enabled
I (410) wifi:config nano formating: disabled
I (410) wifi:Init data frame dynamic rx buffer num: 32
I (420) wifi:Init management frame dynamic rx buffer num: 32
I (420) wifi:Init management short buffer num: 32
I (430) wifi:Init dynamic tx buffer num: 32
I (430) wifi:Init static tx FG buffer num: 2
I (440) wifi:Init static rx buffer size: 1600
I (440) wifi:Init static rx buffer num: 10
I (450) wifi:Init dynamic rx buffer num: 32
I (450) wifi_init: rx ba win: 6
I (450) wifi_init: tcpip mbox: 32
I (460) wifi_init: udp mbox: 6
I (460) wifi_init: tcp mbox: 6
I (460) wifi_init: tcp tx win: 5744
I (470) wifi_init: tcp rx win: 5744
I (470) wifi_init: tcp mss: 1440
I (480) wifi_init: WiFi IRAM OP enabled
I (480) wifi_init: WiFi RX IRAM OP enabled
I (490) phy_init: phy_version 503,13653eb,Jun  1 2022,17:47:08
I (530) wifi:mode : sta (7c:df:a1:e3:5f:50)
I (530) wifi:enable tsf
I (3030) WIFI SCAN: Total Wifi Access Pointss scanned: 18

I (3030) WIFI SCAN:            SSID: ESP32S3_5554
I (3030) WIFI SCAN:            RSSI: -46
I (3030) WIFI SCAN:         Authmod: WIFI_AUTH_OPEN
I (3040) WIFI SCAN: Pairwise Cipher: WIFI_CIPHER_TYPE_NONE
I (3040) WIFI SCAN:    Group Cipher: WIFI_CIPHER_TYPE_NONE
I (3050) WIFI SCAN:         Channel: 1
...
```