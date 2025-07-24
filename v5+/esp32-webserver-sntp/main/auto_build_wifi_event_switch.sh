#!/usr/bin/env bash
#
# A bash script to convert the wifi event enumerations in esp_wifi_types.h
# into C/C++ switch statements that are then pasted into my bigger source file,
# wifi_support.cpp
#
# I did this to avoid missing anything and mispelling anything. And it was a lot
# faster to do it this way than totally by hand.
#
data=$(
    cat <<'EOF'
    WIFI_EVENT_WIFI_READY = 0,           /**< WiFi ready */
    WIFI_EVENT_SCAN_DONE,                /**< Finished scanning AP */
    WIFI_EVENT_STA_START,                /**< Station start */
    WIFI_EVENT_STA_STOP,                 /**< Station stop */
    WIFI_EVENT_STA_CONNECTED,            /**< Station connected to AP */
    WIFI_EVENT_STA_DISCONNECTED,         /**< Station disconnected from AP */
    WIFI_EVENT_STA_AUTHMODE_CHANGE,      /**< the auth mode of AP connected by device's station changed */

    WIFI_EVENT_STA_WPS_ER_SUCCESS,       /**< Station wps succeeds in enrollee mode */
    WIFI_EVENT_STA_WPS_ER_FAILED,        /**< Station wps fails in enrollee mode */
    WIFI_EVENT_STA_WPS_ER_TIMEOUT,       /**< Station wps timeout in enrollee mode */
    WIFI_EVENT_STA_WPS_ER_PIN,           /**< Station wps pin code in enrollee mode */
    WIFI_EVENT_STA_WPS_ER_PBC_OVERLAP,   /**< Station wps overlap in enrollee mode */

    WIFI_EVENT_AP_START,                 /**< Soft-AP start */
    WIFI_EVENT_AP_STOP,                  /**< Soft-AP stop */
    WIFI_EVENT_AP_STACONNECTED,          /**< a station connected to Soft-AP */
    WIFI_EVENT_AP_STADISCONNECTED,       /**< a station disconnected from Soft-AP */
    WIFI_EVENT_AP_PROBEREQRECVED,        /**< Receive probe request packet in soft-AP interface */

    WIFI_EVENT_FTM_REPORT,               /**< Receive report of FTM procedure */

    /* Add next events after this only */
    WIFI_EVENT_STA_BSS_RSSI_LOW,         /**< AP's RSSI crossed configured threshold */
    WIFI_EVENT_ACTION_TX_STATUS,         /**< Status indication of Action Tx operation */
    WIFI_EVENT_ROC_DONE,                 /**< Remain-on-Channel operation complete */

    WIFI_EVENT_STA_BEACON_TIMEOUT,       /**< Station beacon timeout */

    WIFI_EVENT_CONNECTIONLESS_MODULE_WAKE_INTERVAL_START,   /**< Connectionless module wake interval start */

    WIFI_EVENT_AP_WPS_RG_SUCCESS,       /**< Soft-AP wps succeeds in registrar mode */
    WIFI_EVENT_AP_WPS_RG_FAILED,        /**< Soft-AP wps fails in registrar mode */
    WIFI_EVENT_AP_WPS_RG_TIMEOUT,       /**< Soft-AP wps timeout in registrar mode */
    WIFI_EVENT_AP_WPS_RG_PIN,           /**< Soft-AP wps pin code in registrar mode */
    WIFI_EVENT_AP_WPS_RG_PBC_OVERLAP,   /**< Soft-AP wps overlap in registrar mode */

    WIFI_EVENT_ITWT_SETUP,              /**< iTWT setup */
    WIFI_EVENT_ITWT_TEARDOWN,           /**< iTWT teardown */
    WIFI_EVENT_ITWT_PROBE,              /**< iTWT probe */
    WIFI_EVENT_ITWT_SUSPEND,            /**< iTWT suspend */

    WIFI_EVENT_NAN_STARTED,              /**< NAN Discovery has started */
    WIFI_EVENT_NAN_STOPPED,              /**< NAN Discovery has stopped */
    WIFI_EVENT_NAN_SVC_MATCH,            /**< NAN Service Discovery match found */
    WIFI_EVENT_NAN_REPLIED,              /**< Replied to a NAN peer with Service Discovery match */
    WIFI_EVENT_NAN_RECEIVE,              /**< Received a Follow-up message */
    WIFI_EVENT_NDP_INDICATION,           /**< Received NDP Request from a NAN Peer */
    WIFI_EVENT_NDP_CONFIRM,              /**< NDP Confirm Indication */
    WIFI_EVENT_NDP_TERMINATED,           /**< NAN Datapath terminated indication */

    WIFI_EVENT_MAX,                      /**< Invalid WiFi event ID */
EOF
)

for line in $data
do
    if [[ $line == *"_"* ]]; then
        #echo $line
        if [[ $line == *"," ]]; then
            enum=${line::-1}
        else
            enum=$line
        fi
        echo -e "\tcase $enum:"
        echo -e "\t\tESP_LOGI(TAG, stringify($enum));"
        echo -e "\t\tbreak;"
    fi
done
