/* Wifi Scan Application

   This code is licensed under Apache Version 2.0, January 2004

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"

#include "esp_wifi_support.hpp"

static const char *TAG = "WIFI";

// Initialize Wi-Fi as an STA.
//
static void wifi_init() {
    ESP_LOGI(TAG, "INIT -------------------");
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}

// Scan for any WiFi access points.
//
static void wifi_scan() {
    ESP_LOGI(TAG, "START ------------------");

    uint16_t DEFAULT_SCAN_LIST_SIZE = CONFIG_EXAMPLE_SCAN_LIST_SIZE;
    wifi_ap_record_t ap_info[DEFAULT_SCAN_LIST_SIZE];
    uint16_t ap_count = 0;
    memset(ap_info, 0, sizeof(ap_info));

    esp_wifi_scan_start(NULL, true);
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&DEFAULT_SCAN_LIST_SIZE, ap_info));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
        esp_wifi_scan_stop();

    ESP_LOGI(TAG, "SCAN RESULTS\n");

    for (int i = 0; (i < DEFAULT_SCAN_LIST_SIZE) && (i < ap_count); i++) {
        ESP_LOGI(TAG, "%15s: %s", "SSID", ap_info[i].ssid);
        ESP_LOGI(TAG, "%15s: %d", "RSSI", ap_info[i].rssi);
        ESP_LOGI(TAG, "%15s: %s", "Authmod",
            decode_wifi_auth_mode(ap_info[i].authmode));
        if (ap_info[i].authmode != WIFI_AUTH_WEP) {
            ESP_LOGI(TAG, "%15s: %s", "Pairwise Cipher",
                decode_wifi_cipher_type(ap_info[i].pairwise_cipher));
            ESP_LOGI(TAG, "%15s: %s", "Group Cipher",
                decode_wifi_cipher_type(ap_info[i].group_cipher));
        }

        ESP_LOGI(TAG, "%15s: %d\n", "Channel", ap_info[i].primary);
    }

    ESP_LOGI(TAG, "END --------------------");
}

extern "C" void app_main(void) {
    // Initialize NVS
    //
    esp_err_t ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    ESP_ERROR_CHECK( ret );
    wifi_init();
    wifi_scan();
}
