#include <esp_log.h>
#include <esp_sntp.h>
#include <esp_netif_sntp.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include <esp_http_server.h>
#include <esp_flash.h>
#include <nvs_flash.h>
#include <esp_netif.h>
#include <esp_netif_types.h>
#include <esp_wifi.h>
#include <lwip/ip4_addr.h>
#include <lwip/err.h>
#include <lwip/sys.h>

#include "wifi_tools.hpp"
#include "neopixel_tools.hpp"
#include "utilities.hpp"

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

const char *EXTERNAL_AP_SSID{"g00gleeeyes"};
const char *EXTERNAL_AP_PWD{"51538688"};

static int connect_retry_count{0};
const uint32_t MAXIMUM_RETRY_COUNT{10};
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
            case WIFI_EVENT_WIFI_READY:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_WIFI_READ));
                break;
            case WIFI_EVENT_SCAN_DONE:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_SCAN_DONE));
                break;
            case WIFI_EVENT_STA_START:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_STA_START));
                esp_wifi_connect();
                break;
            case WIFI_EVENT_STA_STOP:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_STA_STOP));
                break;
            case WIFI_EVENT_STA_CONNECTED:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_STA_CONNECTED));
                break;
            case WIFI_EVENT_STA_DISCONNECTED:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_STA_DISCONNECTED));
                if (connect_retry_count < MAXIMUM_RETRY_COUNT) {
                    ESP_LOGI(TAG, "RECONNECT ATTEMPT %i", ++connect_retry_count);
                    esp_wifi_connect();
                }
                else {
                    ESP_LOGI(TAG, "RECONNECT FAILURE");
                    xEventGroupSetBits(wifi_event_group, WIFI_FAIL_BIT);
                }
                break;
            case WIFI_EVENT_STA_AUTHMODE_CHANGE:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_STA_AUTHMODE_CHANGE));
                break;
            case WIFI_EVENT_STA_WPS_ER_SUCCESS:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_STA_WPS_ER_SUCCESS));
                break;
            case WIFI_EVENT_STA_WPS_ER_FAILED:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_STA_WPS_ER_FAILED));
                break;
            case WIFI_EVENT_STA_WPS_ER_TIMEOUT:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_STA_WPS_ER_TIMEOUT));
                break;
            case WIFI_EVENT_STA_WPS_ER_PIN:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_STA_WPS_ER_PIN));
                break;
            case WIFI_EVENT_STA_WPS_ER_PBC_OVERLAP:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_STA_WPS_ER_PBC_OVERLAP));
                break;
            case WIFI_EVENT_AP_START:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_AP_START));
                esp_wifi_connect();
                break;
            case WIFI_EVENT_AP_STOP:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_AP_STOP));
                break;
            case WIFI_EVENT_AP_STACONNECTED:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_AP_STACONNECTED));
                break;
            case WIFI_EVENT_AP_STADISCONNECTED:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_AP_STADISCONNECTED));
                esp_wifi_connect();
                break;
            case WIFI_EVENT_AP_PROBEREQRECVED:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_AP_PROBEREQRECVED));
                break;
            case WIFI_EVENT_FTM_REPORT:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_FTM_REPORT));
                break;
            case WIFI_EVENT_STA_BSS_RSSI_LOW:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_STA_BSS_RSSI_LOW));
                break;
            case WIFI_EVENT_ACTION_TX_STATUS:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_ACTION_TX_STATUS));
                break;
            case WIFI_EVENT_ROC_DONE:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_ROC_DONE));
                break;
            case WIFI_EVENT_STA_BEACON_TIMEOUT:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_STA_BEACON_TIMEOUT));
                print_time();
                break;
            case WIFI_EVENT_CONNECTIONLESS_MODULE_WAKE_INTERVAL_START:
                ESP_LOGI(TAG,
                    stringify(WIFI_EVENT_CONNECTIONLESS_MODULE_WAKE_INTERVAL_START));
                break;
            case WIFI_EVENT_AP_WPS_RG_SUCCESS:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_AP_WPS_RG_SUCCESS));
                break;
            case WIFI_EVENT_AP_WPS_RG_FAILED:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_AP_WPS_RG_FAILED));
                break;
            case WIFI_EVENT_AP_WPS_RG_TIMEOUT:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_AP_WPS_RG_TIMEOUT));
                break;
            case WIFI_EVENT_AP_WPS_RG_PIN:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_AP_WPS_RG_PIN));
                break;
            case WIFI_EVENT_AP_WPS_RG_PBC_OVERLAP:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_AP_WPS_RG_PBC_OVERLAP));
                break;
            case WIFI_EVENT_ITWT_SETUP:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_ITWT_SETUP));
                break;
            case WIFI_EVENT_ITWT_TEARDOWN:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_ITWT_TEARDOWN));
                break;
            case WIFI_EVENT_ITWT_PROBE:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_ITWT_PROBE));
                break;
            case WIFI_EVENT_ITWT_SUSPEND:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_ITWT_SUSPEND));
                break;
            case WIFI_EVENT_NAN_STARTED:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_NAN_STARTED));
                break;
            case WIFI_EVENT_NAN_STOPPED:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_NAN_STOPPED));
                break;
            case WIFI_EVENT_NAN_SVC_MATCH:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_NAN_SVC_MATCH));
                break;
            case WIFI_EVENT_NAN_REPLIED:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_NAN_REPLIED));
                break;
            case WIFI_EVENT_NAN_RECEIVE:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_NAN_RECEIVE));
                break;
            case WIFI_EVENT_NDP_INDICATION:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_NDP_INDICATION));
                break;
            case WIFI_EVENT_NDP_CONFIRM:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_NDP_CONFIRM));
                break;
            case WIFI_EVENT_NDP_TERMINATED:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_NDP_TERMINATED));
                break;
            case WIFI_EVENT_MAX:
                ESP_LOGI(TAG, stringify(WIFI_EVENT_MAX));
                break;
        }
    }
    else if (event_base == IP_EVENT) {
        switch (event_id) {
            case IP_EVENT_STA_GOT_IP: {
                ip_event_got_ip_t *evt =
                    reinterpret_cast<ip_event_got_ip_t *>(event_data);
                ESP_LOGI(TAG, stringify(IP_EVENT_STA_GOT_IP) ": " IPSTR,
                    IP2STR(&evt->ip_info.ip));
                connect_retry_count = 0;
                xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
            }
                break;
            case IP_EVENT_STA_LOST_IP:
                ESP_LOGI(TAG, stringify(IP_EVENT_STA_LOST_IP));
                break;
            case IP_EVENT_AP_STAIPASSIGNED:
                ESP_LOGI(TAG, stringify(IP_EVENT_AP_STAIPASSIGNED));
                break;
            case IP_EVENT_GOT_IP6:
                ESP_LOGI(TAG, stringify(IP_EVENT_GOT_IP6));
                break;
            case IP_EVENT_ETH_GOT_IP:
                ESP_LOGI(TAG, stringify(IP_EVENT_ETH_GOT_IP));
                break;
            case IP_EVENT_ETH_LOST_IP:
                ESP_LOGI(TAG, stringify(IP_EVENT_ETH_LOST_IP));
                break;
            case IP_EVENT_PPP_GOT_IP:
                ESP_LOGI(TAG, stringify(IP_EVENT_PPP_GOT_IP));
                break;
            case IP_EVENT_PPP_LOST_IP: {
                ESP_LOGI(TAG, stringify(IP_EVENT_PPP_LOST_IP));
            }
                break;
            default:
                ESP_LOGI(TAG, "UNCAUGHT IP_EVENT");
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
        ESP_LOGI(TAG, "FAILED TO UPDATE SYSTEM TIME VIA NTP");
    }

    // Eastern Daylight Saving Time.
    //
    setenv("TZ", "EST5EDT,M3.2.0/2,M11.1.0", 1);
    tzset();
    print_time();
}
//
// Initialize WiFi.
//
esp_err_t initialize_wifi(const char *SSID) {
    string _SSID{SSID};
    //
    // Required by WiFi driver.
    //
    ESP_LOGI(TAG, "INITIALISE NVS FLASH");
    esp_err_t ret = nvs_flash_init();
    //
    // If initialization fails then erase non-volatile storage and try again.
    //
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES or
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
            ESP_LOGI(TAG, "ERASE NVS FLASH");
            ESP_ERROR_CHECK(nvs_flash_erase());
            ret = nvs_flash_init();
        }

    ESP_ERROR_CHECK(ret);
    //
    // Create a FreeRTOS new event group. The return value will be non-null if
    // successful, or null if it fails. It will fail if there is insufficient
    // FreeRTOS heap available.
    //
    // This is taken from Espressif's example code.
    // We don't check for failure here and that's a problem.
    // The bigger issue is what do we do if it does fail?
    // There is nothing in the Espressif documentation to explain that.
    //
    wifi_event_group = xEventGroupCreate();
    //
    // The following is needed to avoid 
    // assert failed: tcpip_send_msg_wait_sem (Invalid mbox)
    //
    ESP_LOGI(TAG, "INITIALISE ESP NETIF");
    ESP_ERROR_CHECK(esp_netif_init());
    //
    // The following is needed to avoid ESP_ERR_INVALID_STATE
    // error when a wifi or httpd instance is created.
    //
    ESP_LOGI(TAG, "CREATE DEFAULT EVENT LOOP");
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_LOGI(TAG, "CREATE DEFAULT WIFI STATION");
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);

    wifi_init_config_t init_config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&init_config));

    ESP_LOGI(TAG, "REGISTER ESP EVENT ANY ID");
    esp_event_handler_instance_t instance_any_id;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(
        WIFI_EVENT, ESP_EVENT_ANY_ID,
        &wifi_event_handler, sta_netif, &instance_any_id));

    ESP_LOGI(TAG, "REGISTER IP EVENT STA GOT IP");
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(
        IP_EVENT, IP_EVENT_STA_GOT_IP,
        &wifi_event_handler, sta_netif, &instance_got_ip));
    //
    // WiFi AP Minimum Configuration
    //
    //wifi_config_t wifi_ap_config;
    //
    // Set SSID.
    //
    //memcpy(wifi_ap_config.ap.ssid, SSID, strlen(SSID));
    //wifi_ap_config.ap.ssid_len = strlen(SSID);
    //
    // Configure the rest.
    //
    //wifi_ap_config.ap.channel = 6;
    //wifi_ap_config.ap.authmode = WIFI_AUTH_OPEN;
    //wifi_ap_config.ap.max_connection = 4;
    //
    // WiFi AP Mode
    //
    //ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    //ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_ap_config));
    ESP_LOGI(TAG, "USING AP SSID: %s", EXTERNAL_AP_SSID);
    ESP_LOGI(TAG, "USING AP PSWD: %s", EXTERNAL_AP_PWD);
    wifi_config_t wifi_config;
    memcpy(wifi_config.sta.ssid, EXTERNAL_AP_SSID, strlen(EXTERNAL_AP_SSID)+1);
    memcpy(wifi_config.sta.password, EXTERNAL_AP_PWD,
        strlen(EXTERNAL_AP_PWD)+1);
    wifi_config.sta.pmf_cfg.required = false;
    wifi_config.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    ret = esp_netif_set_hostname(sta_netif , SSID);
    const char *host_msg = (ret == ESP_OK ? "SUCCESS" : "FAILURE");
    ESP_LOGI(TAG, "SET HOST NAME: %s", host_msg);

    if (ret != ESP_OK) {
        return ESP_FAIL;
    }

    EventBits_t bits = xEventGroupWaitBits(wifi_event_group,
        WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
        pdFALSE,
        pdFALSE,
        portMAX_DELAY);

    const char *conn_msg = (bits & WIFI_CONNECTED_BIT ? "SUCCESS" : "FAILURE");

    ESP_LOGI(TAG, "INITIALIZE WIFI: CONNECTION %s", conn_msg);

    if (bits & WIFI_CONNECTED_BIT) {
        initialize_sntp();
    }

    ESP_LOGI(TAG, "INITIALIZE WIFI DONE");
    return ESP_OK;
}
//
// This is an experiment to create the ability for an ESP32-S3 to act as
// a stand-alone access point. I've done this with MicroPython, but can't
// seem (so far) to do this within the ESP-IDF framework.
//
void set_static_ip(esp_netif_t *netif) {
    if (esp_netif_dhcpc_stop(netif) != ESP_OK) {
        ESP_LOGE(TAG, "FAILED TO STOP DHCP CLIENT");
        return;
    }

    esp_netif_ip_info_t ip_info;
    memset(&ip_info, 0, sizeof(esp_netif_ip_info_t));
    ip_info.ip.addr = ipaddr_addr("192.168.1.2");
    ip_info.netmask.addr = ipaddr_addr("255.255.255.0");
    ip_info.gw.addr = ipaddr_addr("192.168.1.1");

    if (esp_netif_set_ip_info(netif, &ip_info) != ESP_OK) {
        ESP_LOGE(TAG, "FAILED TO SET STATIC IP");
        return;
    }
}
