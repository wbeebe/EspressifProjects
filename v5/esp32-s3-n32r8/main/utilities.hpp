#pragma once
#include <string>

using std::string;

static const char *TAG = "ESP32-S3-DevKitC-1.1-N32R8";

void comma_format_number(uint32_t value, string &results);
const char *get_time_now();
void print_time();
