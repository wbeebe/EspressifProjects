#include <string>
#include <esp_log.h>
#include <esp_chip_info.h>
#include <esp_mac.h>
#include <esp_flash.h>

#include "webserver.hpp"
#include "neopixel_tools.hpp"
#include "utilities.hpp"
//
// Right now the web page is embedded with the code. I've done this in the past
// with MicroPython and later CircuitPython.
//
// I need to find a way to move all web page content out of the code body and
// onto the flash, and open it like a regular data file.
//
static std::string _SSID;
static std::string _webpage;
//
void webpage() {
    std::string heap_size;
    comma_format_number(esp_get_free_heap_size(), heap_size);
    uint32_t nflash_size{0};
    std::string flash_size;
    esp_flash_get_size(NULL, &nflash_size);
    comma_format_number(nflash_size, flash_size);
    _webpage.clear();
    _webpage =
"<!DOCTYPE html>"
"<html>"
"<head>"
"<meta http-equiv=\"Content-type\" content=\"text/html;charset=utf-8\">"
"<title>" + _SSID + "</title>"
"<style>"
"body { font-family: sans-serif; margin: 20px; }"
"button {"
"   font-weight: normal;"
"   display: inline-block;"
"   width: 99%;"
"   border: none;"
"   border-radius: 4px;"
"   color: #ffffff;"
"   padding: 16px 40px;"
"   text-decoration: none;"
"   font-size: 500%;"
"   margin: 2px;"
"   justify-content: center;"
"   align-items: center;"
"   outline: none;"
"}"
".button-red { background-color: #DC143C; }"
".button-green { background-color: #20A020; }"
".button-blue { background-color: #4080E0; }"
".button-gray { background-color: #808080; }"
".button-off { background-color: #404040; }"
"hr { border: 0;height: 2px;"
"background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 0, 0.75), rgba(0, 0, 0, 0));}"
"h1 { font-size: 500%; color: #D35F8D; text-align: center; }"
"h2 { font-size: 250%; color: #5FA3D3; padding-left: 15px; }"
"<link rel=\"icon\" href=\"data:,\">"
"</style>"
"</head><body>"
"<h1>" + _SSID + "</h1>"
"<hr/>"
"<form accept-charset=\"utf-8\" method=\"POST\">"
"<button class='button-red'   name=\"RED\"   value=\"ON\">Red</button>"
"<button class='button-green' name=\"GREEN\" value=\"ON\">Green</button>"
"<button class='button-blue'  name=\"BLUE\"  value=\"ON\">Blue</button>"
"<button class='button-off'   name=\"OFF\"   value=\"OFF\">Off</button>"
"<button class='button-gray'  name=\"CYCLE\" value=\"ON\">Cycle</button>"
"</form>"
"<hr/>"
"<h2>Memory free: " + heap_size + " bytes<br/>"
"Flash free: " + flash_size + " bytes<br/>"
"ESP-IDF " + esp_get_idf_version() + "</h2>"
"<h2> " + get_time_now() + "</h2>"
"</body></html>";
}

esp_err_t send_root_web_page(httpd_req_t *req) {
    webpage();
    httpd_resp_send_chunk(req, _webpage.c_str(), HTTPD_RESP_USE_STRLEN);
    return httpd_resp_send_chunk(req, "", 0);
}

esp_err_t send_favicon(httpd_req_t *req) {
    return ESP_OK;
}

esp_err_t set_device_feature(httpd_req_t *req) {
    int content_len = req->content_len;
    // ESP_LOGI(TAG, "CONTENT LENGTH %d", content_len);
    char buffer[100];
    httpd_req_recv(req, buffer, req->content_len);
    buffer[content_len] = 0;
    // ESP_LOGI(TAG, "CONTENT %s", buffer);

    if (strcmp(buffer, "RED=ON") == 0) {
        set_neopixel_red();
    }
    else if (strcmp(buffer, "GREEN=ON") == 0) {
        set_neopixel_green();
    }
    else if (strcmp(buffer, "BLUE=ON") == 0) {
        set_neopixel_blue();
    }
    else if (strcmp(buffer, "OFF=OFF") == 0) {
        clear_neopixel();
    }
    else if (strcmp(buffer, "CYCLE=ON") == 0) {
        color_cycle_neopixel();
    }

    webpage();
    httpd_resp_send_chunk(req, _webpage.c_str(), HTTPD_RESP_USE_STRLEN);
    httpd_resp_send_chunk(req, NULL, 0);
    return ESP_OK;
}
//
//
//
static httpd_uri_t uri_favicon = {
    .uri = "/favicon.ico",
    .method = HTTP_GET,
    .handler = send_favicon,
    .user_ctx = NULL
};

static httpd_uri_t uri_root = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = send_root_web_page,
    .user_ctx = NULL
};

static httpd_uri_t uri_post = {
    .uri = "/",
    .method = HTTP_POST,
    .handler = set_device_feature,
    .user_ctx = NULL
};
//
//
//
httpd_handle_t initialize_webserver(const std::string &SSID) {
    _SSID = SSID;
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;

    // Start the HTTP server.
    //
    if (httpd_start(&server, &config) == ESP_OK) {
        ESP_LOGI(TAG, "WEBSERVER SUCCESSFUL STARTUP");
        httpd_register_uri_handler(server, &uri_favicon);
        httpd_register_uri_handler(server, &uri_root);
        httpd_register_uri_handler(server, &uri_post);
    }
    else {
        ESP_LOGI(TAG, "WEBSERVER FAILED STARTUP");
        server = NULL;
    }

    return server;
}
