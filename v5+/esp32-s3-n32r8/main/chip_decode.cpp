#include "chip_decode.hpp"

void translate_esp_chip_model(esp_chip_model_t model, string &results) {
    switch(model) {
        case CHIP_ESP32:   results = "ESP32"; return;
        case CHIP_ESP32S2: results = "ESP32S2"; return;
        case CHIP_ESP32S3: results = "ESP32S3"; return;
        case CHIP_ESP32C2: results = "ESP32C2"; return;
        case CHIP_ESP32C3: results = "ESP32C3"; return;
        case CHIP_ESP32C6: results = "ESP32C6"; return;
        case CHIP_ESP32H2: results = "ESP32H2"; return;
        case CHIP_POSIX_LINUX: results = "POSIX_LINUX"; return;
        default: results = "CHIP_UNKNOWN";
    }
}

void decode_features(uint32_t features, string &results) {
    if (features == 0) {
        results = "NO_FEATURES";
    }
    else {
        if (features & CHIP_FEATURE_EMB_FLASH) results += "FLASH ";
        if (features & CHIP_FEATURE_WIFI_BGN) results += "WIFI ";
        if (features & CHIP_FEATURE_BLE) results += "BLE ";
        if (features & CHIP_FEATURE_BT) results += "BT ";
        if (features & CHIP_FEATURE_IEEE802154) results += "IEEE802154 ";
        if (features & CHIP_FEATURE_EMB_PSRAM) results += "PSRAM";
    }
}
