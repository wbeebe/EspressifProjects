#include <esp_log.h>
#include <esp_netif_sntp.h>

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

#include <esp_http_server.h>
#include <esp_flash.h>
#include <esp_netif.h>
#include <esp_netif_types.h>
#include <esp_wifi.h>
#include <lwip/ip4_addr.h>
#include <lwip/err.h>

#include "wifi_tools.h"
static const char *TAG = "ESP32-S3-DevKitC-1.1-N32R8";

// FreeRTOS event group to signal when we're connected.
//
static EventGroupHandle_t wifi_event_group;
//
// The event group allows multiple bits for many events,
// but we only care about two events:
// - connected to the access point with an IP
// - connection failure after the maximum retry count
//
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

#define EXTERNAL_AP_SSID "YOUR LOCAL WIFI SSID"
#define EXTERNAL_AP_PWD "YOU LOCAL WIFI PASSWORD"

static int connect_retry_count = 0;
const uint32_t MAXIMUM_RETRY_COUNT = 10;
//
// This switch statement has gotten large and complex.
// An alternative might be an array with the enumerations indexing into
// pointers to structures that contain a pointer to a function, although
// I don't know how that would be any less complex.
//
void wifi_event_handler (void *arg,
    esp_event_base_t event_base, int32_t event_id, void *event_data) {

    if (event_base == WIFI_EVENT) {
        switch (event_id) {
            case WIFI_EVENT_STA_START:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_STA_START));
                esp_wifi_connect();
                break;
            case WIFI_EVENT_STA_DISCONNECTED:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_STA_DISCONNECTED));
                if (connect_retry_count < MAXIMUM_RETRY_COUNT) {
                    ESP_LOGI(TAG, "WIFI RECONNECT ATTEMPT %i", ++connect_retry_count);
                    esp_wifi_connect();
                }
                else {
                    ESP_LOGI(TAG, "WIFI RECONNECT FAILURE");
                    xEventGroupSetBits(wifi_event_group, WIFI_FAIL_BIT);
                }
                break;
            default:
                ESP_LOGI(TAG, "WIFI UNCAUGHT WIFI_EVENT %d", (int)event_id);
                break;
        }
    }
    else if (event_base == IP_EVENT) {
        switch (event_id) {
            case IP_EVENT_STA_GOT_IP: {
                ip_event_got_ip_t *evt = (ip_event_got_ip_t *)event_data;
                ESP_LOGI(TAG, stringify(IP_EVENT_STA_GOT_IP) ": " IPSTR,
                    IP2STR(&evt->ip_info.ip));
                connect_retry_count = 0;
                xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
            }
                break;
            default:
                ESP_LOGI(TAG, "WIFI UNCAUGHT IP_EVENT %d", (int)event_id);
        }
    }
}
//
// All the heavy lifting to initialize WiFi and SNTP subsystems on the
// ESP32-S3 based micro-controllers. This sets up the chip WiFi as a station
// connected to a local external WiFi access point.
//
// The initialize_sntp function initializes SNTP. Time is set to Eastern
// Standard Time.
//
// Note that I DID NOT use the ESP_NETIF_SNTP_DEFAULT_CONFIG... macros because
// under C++ the macro fails. I thus use these alternative function calls.
// It looks as if someone working the software at Espressif knows this and
// developed these alternatives.
//
// Note that these function calls are supported in ESP-IDF 5.2-dev and possibly
// later. Older code for older ESP-IDF releases currently on the web that does
// not have the esp_ prefix will emit deprecation warning errors.
//
void initialize_sntp() {
    esp_sntp_config_t config = ESP_NETIF_SNTP_DEFAULT_CONFIG("pool.ntp.org");
    esp_netif_sntp_init(&config);

    if (esp_netif_sntp_sync_wait(pdMS_TO_TICKS(10000)) != ESP_OK) {
        ESP_LOGI(TAG, "WIFI FAILED TO UPDATE SYSTEM TIME VIA NTP");
    }

    // Eastern Daylight Saving Time.
    //
    setenv("TZ", "EST5EDT,M3.2.0/2,M11.1.0", 1);
    tzset();
    //print_time();
}
//
// Initialize WiFi.
//
esp_err_t initialize_wifi_station(const char *SSID) {
    ESP_LOGI(TAG, "WIFI CREATE EVENT GROUP");
    wifi_event_group = xEventGroupCreate();
    //
    ESP_LOGI(TAG, "WIFI INITIALISE NETIF");
    ESP_ERROR_CHECK(esp_netif_init());
    //
    ESP_LOGI(TAG, "WIFI CREATE DEFAULT EVENT LOOP");
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    bool result = esp_netif_set_hostname(sta_netif , SSID) == ESP_OK;
    ESP_LOGI(TAG, "WIFI SET HOST NAME TO %s: %s", SSID, (result ? "SUCCESS" : "FAILURE"));

    ESP_LOGI(TAG, "WIFI CREATE DEFAULT WIFI STATION");
    wifi_init_config_t init_config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&init_config));

    ESP_LOGI(TAG, "WIFI REGISTER ESP EVENT ANY ID");
    esp_event_handler_instance_t instance_any_id;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(
        WIFI_EVENT,
        ESP_EVENT_ANY_ID,
        &wifi_event_handler,
        NULL,
        &instance_any_id));

    ESP_LOGI(TAG, "WIFI REGISTER IP EVENT STA GOT IP");
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(
        IP_EVENT,
        IP_EVENT_STA_GOT_IP,
        &wifi_event_handler,
        NULL,
        &instance_got_ip));
    //
    //
    ESP_LOGI(TAG, "WIFI USING AP SSID: %s", EXTERNAL_AP_SSID);
    ESP_LOGI(TAG, "WIFI USING AP PSWD: %s", EXTERNAL_AP_PWD);

    wifi_config_t wifi_config = {
            .sta = {
                    .ssid = EXTERNAL_AP_SSID,
                    .password = EXTERNAL_AP_PWD,
                    /* Authmode threshold resets to WPA2 as default if password matches WPA2 standards (pasword len => 8).
                     * If you want to connect the device to deprecated WEP/WPA networks, Please set the threshold value
                     * to WIFI_AUTH_WEP/WIFI_AUTH_WPA_PSK and set the password with length and format matching to
                     * WIFI_AUTH_WEP/WIFI_AUTH_WPA_PSK standards.
                     */
                    .threshold.authmode = WIFI_AUTH_WPA_WPA2_PSK,
            },
    };


    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    EventBits_t bits = xEventGroupWaitBits(wifi_event_group,
        WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
        pdFALSE,
        pdFALSE,
        portMAX_DELAY);

    const char *conn_msg = (bits & WIFI_CONNECTED_BIT ? "SUCCESS" : "FAILURE");

    ESP_LOGI(TAG, "WIFI INITIALIZE: CONNECTION %s", conn_msg);

    if (bits & WIFI_CONNECTED_BIT) {
        initialize_sntp();
        ESP_LOGI(TAG, "WIFI SUCCESSFUL INITIALIZATION");
        return ESP_OK;
    }
    else {
        ESP_LOGI(TAG, "WIFI FAILED INITIALIZATION");
        return ESP_FAIL;
    }
}
//
// This is an experiment to create the ability for an ESP32-S3 to act as
// a stand-alone access point. I've done this with MicroPython, but can't
// seem (so far) to do this within the ESP-IDF framework.
//
void set_static_ip(esp_netif_t *netif) {
    if (esp_netif_dhcpc_stop(netif) != ESP_OK) {
        ESP_LOGE(TAG, "WIFI FAILED TO STOP DHCP CLIENT");
        return;
    }

    esp_netif_ip_info_t ip_info;
    memset(&ip_info, 0, sizeof(esp_netif_ip_info_t));
    ip_info.ip.addr = ipaddr_addr("192.168.4.2");
    ip_info.netmask.addr = ipaddr_addr("255.255.255.0");
    ip_info.gw.addr = ipaddr_addr("192.168.4.1");

    if (esp_netif_set_ip_info(netif, &ip_info) != ESP_OK) {
        ESP_LOGE(TAG, "WIFI FAILED TO SET STATIC IP");
        return;
    }
}
