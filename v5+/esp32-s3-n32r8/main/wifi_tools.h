#pragma once

#define stringify( _name ) #_name
esp_err_t initialize_wifi_station(const char *SSID);
