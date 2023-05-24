#include <esp_log.h>
#include <esp_sntp.h>
#include <esp_netif_sntp.h>

#include "utilities.hpp"
//
// The things I have to do to format numbers with commas.
// Not at all simple like Python's {:,}
//
void comma_format_number(uint32_t value, string &results) {
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
