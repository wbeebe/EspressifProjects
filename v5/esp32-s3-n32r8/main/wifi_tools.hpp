#pragma once

#include <string>

using std::string;
#define stringify( _name ) #_name

void initialize_wifi(const char *SSID);
