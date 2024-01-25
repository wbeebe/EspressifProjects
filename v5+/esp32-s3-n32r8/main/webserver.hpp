#pragma once

#include <esp_http_server.h>
#include "utilities.hpp"

httpd_handle_t initialize_webserver(const std::string &SSID);
