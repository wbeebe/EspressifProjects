#pragma once

#include <string>

using std::string;
#define stringify( _name ) #_name

esp_err_t initialize_wifi(const char *SSID);
