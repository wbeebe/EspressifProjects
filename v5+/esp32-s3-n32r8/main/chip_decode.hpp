#pragma once

#include <array>
#include <cinttypes>
#include <string>

#include <esp_chip_info.h>

using std::string;
#define stringify( _name ) #_name

void translate_esp_chip_model(esp_chip_model_t model, string &results);
void decode_features(uint32_t features, string &results);