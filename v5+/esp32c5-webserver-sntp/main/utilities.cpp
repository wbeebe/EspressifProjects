/*
 * Copyright 2025 William H. Beebe, Jr.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <esp_log.h>
#include <esp_sntp.h>
#include <esp_netif_sntp.h>

#include "common.h"
#include "utilities.hpp"
//
// The things I have to do to format numbers with commas.
// Not at all simple like Python's {:,}
//
void comma_format_number(uint32_t value, std::string &results) {
    results = std::to_string(value);
    int n = results.length() - 3;
    while (n > 0) {
        results.insert(n, ",");
        n -= 3;
    }
}

static char strftime_buf[64];
static time_t now;
static struct tm timeinfo;

const char *get_time_now() {
    time(&now);
    localtime_r(&now, &timeinfo);
    strftime(strftime_buf, sizeof(strftime_buf), "%a %e %b %Y %r %Z", &timeinfo);
    return strftime_buf;
}

void print_time() {
    ESP_LOGI(TAG, "TIME: %s", get_time_now());
}
