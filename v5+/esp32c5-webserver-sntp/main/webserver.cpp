/*
 * Copyright 2025,2026 William H. Beebe, Jr.
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
#include <string>
#include <esp_log.h>
#include <esp_chip_info.h>
#include <esp_mac.h>
#include <esp_flash.h>

#include "common.h"
#include "webserver.hpp"
#include "neopixel_tools.hpp"
#include "utilities.hpp"

typedef enum ButtonState {
    NO_BUTTON,
    RED_BUTTON,
    GREEN_BUTTON,
    BLUE_BUTTON,
} button_state_t;
button_state_t last_button = NO_BUTTON;

std::string red_state = "button-red-off";
std::string blue_state = "button-blue-off";
std::string green_state = "button-green-off";

void set_button_off() {
    switch(last_button) {
        case RED_BUTTON: red_state = "button-red-off"; break;
        case GREEN_BUTTON: green_state = "button-green-off"; break;
        case BLUE_BUTTON: blue_state = "button-blue-off"; break;
        default: break;
    }
    last_button = NO_BUTTON;
}
//
// The web page is embedded within code.
//
static std::string _SSID;
static std::string _webpage;

void regenerate_webpage() {
    std::string heap_size;
    comma_format_number(esp_get_free_heap_size(), heap_size);
    uint32_t nflash_size{0};
    std::string flash_size;
    esp_flash_get_size(NULL, &nflash_size);
    comma_format_number(nflash_size, flash_size);
    _webpage.clear();
    _webpage =
"<html>"
"<head>"
"<meta http-equiv=\"Content-type\" content=\"text/html;charset=utf-8\">"
"<title>" + _SSID + "</title>"
"<style>"
"html {"
"   font-family: sans-serif;"
"   background-color: #FFFFFF;"
"   display: inline-block;"
"   margin: 20px;"
"   }"
"button {"
"   font-size: 500%;"
"   font-weight: normal;"
"   display: inline-block;"
"   margin: 5px;"
"   padding: 20px 60px;"
"   width: 99%;"
"   height: 150px;"
"   justify-content: center;"
"   text-decoration: none;"
"   color: #ffffff;"
"   border: none;"
"   border-radius: 15px;"
"   outline: none;"
"}"
".button-red-on { background-color: #DC143C; }"
".button-red-off { color: #DC143C; border: 10px solid; background-color: #FFFFFF; }"
".button-green-on { background-color: #20A020; }"
".button-green-off { color: #20A020; border: 10px solid; background-color: #FFFFFF; }"
".button-blue-on { background-color: #4080E0; }"
".button-blue-off { color: #4080E0; border: 10px solid; background-color: #FFFFFF; }"
".button-gray { background-color: #808080; }"
".button-off { background-color: #404040; }"
"h1 { font-size: 500%; color: #D35F8D; text-align: center; margin-top: 10px; margin-bottom: 10px; }"
"h2 { font-size: 300%; color: #5FA3D3; padding-left: 15px; }"
"<link rel=\"icon\" href=\"data:,\">"
"</style>"
"</head><body>"
"<h1>" + _SSID + "</h1>"
"<form accept-charset=\"utf-8\" method=\"POST\">"
"<button class='" + red_state + "'   name=\"RED\"   value=\"ON\">Red</button>"
"<button class='" + green_state + "' name=\"GREEN\" value=\"ON\">Green</button>"
"<button class='" + blue_state + "'  name=\"BLUE\"  value=\"ON\">Blue</button>"
"<button class='button-gray'  name=\"CYCLE\" value=\"ON\">Cycle</button>"
"</form>"
"<h2> " + get_time_now() + "</h2>"
"<h2>" + TAG + "<br/>"
"Last built: " + __TIME__ + " on " + __DATE__ + "<br/>"
"Memory free: " + heap_size + " bytes<br/>"
"Flash free: " + flash_size + " bytes<br/>"
"Built with ESP-IDF " + esp_get_idf_version() + "</h2>"
"</body></html>";
}

esp_err_t send_root_web_page(httpd_req_t *req) {
    regenerate_webpage();
    return httpd_resp_send(req, _webpage.c_str(), HTTPD_RESP_USE_STRLEN);
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
        set_button_off();
        if (set_neopixel_red()){
            red_state = "button-red-on";
            last_button = RED_BUTTON;
        }
    }
    else if (strcmp(buffer, "GREEN=ON") == 0) {
        set_button_off();
        if (set_neopixel_green()) {
            green_state = "button-green-on";
            last_button = GREEN_BUTTON;
        }
    }
    else if (strcmp(buffer, "BLUE=ON") == 0) {
        set_button_off();
        if (set_neopixel_blue()) {
            blue_state = "button-blue-on";
            last_button = BLUE_BUTTON;
        }
    }
    else if (strcmp(buffer, "CYCLE=ON") == 0) {
        set_button_off();
        color_blend_neopixel();
    }

    regenerate_webpage();
    return httpd_resp_send(req, _webpage.c_str(), HTTPD_RESP_USE_STRLEN);
}

// For all the Apple request crap.
static httpd_uri_t uri_apple1 = {
    .uri = "/apple-touch-icon-120x120-precomposed.png",
    .method = HTTP_GET,
    .handler = send_favicon,
    .user_ctx = NULL
};

static httpd_uri_t uri_apple2 = {
    .uri = "/apple-touch-icon-120x120.png",
    .method = HTTP_GET,
    .handler = send_favicon,
    .user_ctx = NULL
};

static httpd_uri_t uri_apple3 = {
    .uri = "/apple-touch-icon-precomposed.png",
    .method = HTTP_GET,
    .handler = send_favicon,
    .user_ctx = NULL
};

static httpd_uri_t uri_apple4 = {
    .uri = "/apple-touch-icon.png",
    .method = HTTP_GET,
    .handler = send_favicon,
    .user_ctx = NULL
};

// For every other request.
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

httpd_handle_t initialize_webserver(const std::string &SSID) {
    ESP_LOGI(TAG, "INITIALIZE_WEBSERVER");
    _SSID = SSID;
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;

    // Start the HTTP server.
    //
    if (httpd_start(&server, &config) == ESP_OK) {
        ESP_LOGI(TAG, "WEBSERVER SUCCESSFUL STARTUP");
        httpd_register_uri_handler(server, &uri_apple1);
        httpd_register_uri_handler(server, &uri_apple2);
        httpd_register_uri_handler(server, &uri_apple3);
        httpd_register_uri_handler(server, &uri_apple4);
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
