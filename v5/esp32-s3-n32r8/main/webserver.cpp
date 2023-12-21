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
static string _page_heading;
//
// This is common to all web pages rendered in a users web browser.
//
void build_page_heading(const string &SSID) {
    _page_heading =
"<!DOCTYPE html>"
"<html>"
"<head>"
"<meta http-equiv=\"Content-type\" content=\"text/html;charset=utf-8\">"
"<title>" + SSID + "</title>"
"<style>"
"body {font-family: sans-serif;margin: 20px;}"
"button {"
"font-size: 300%;"
"font-weight: normal;"
"display: inline-block;"
"margin: 5px;"
"padding: 20px 60px;"
"width: 99%;"
"height: 150px;"
"justify-content: center;"
"align-items: center;"
"text-decoration: none;"
"color: #ffffff;"
"background-color: #556B2F;"
"border: none;"
"border-radius: 10px;"
"outline: none;}"
"hr {border: 0;height: 2px;"
"background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 0, 0.75), rgba(0, 0, 0, 0));}"
"h1 {font-size: 300%; color: #D35F8D; text-align: center;}"
"h2 {font-size: 250%; color: #5FA3D3; padding-left: 15px;}"
"<link rel=\"icon\" href=\"data:,\">"
"</style>"
"</head><body>"
"<h1>" + SSID + "</h1>"
"<hr/>";
}

static string _webpage;

void build_main_webpage() {
    _webpage = _page_heading +
"<a href=\"/red\"><button style='background-color: #DC143C'>Red</button></a>"
"<a href=\"/green\"><button style='background-color: #228B22'>Green</button></a>"
"<a href=\"/blue\"><button style='background-color: #4169E1'>Blue</button></a>"
"<a href=\"/cycle\"><button style='background-color: #808080'>Cycle</button></a>"
"<a href=\"/off\"><button style='background-color: #404040'>OFF</button></a>";
}
//
// The footer is rendered individually because it displays dynamic data on each
// page sent to the user, and because it's used on more than one web page,
// the main page and the Home button.
//
static string _footer;

void build_web_page_footer(string &footer) {
    string heap_size;
    comma_format_number(esp_get_free_heap_size(), heap_size);
    uint32_t nflash_size{0};
    string flash_size;
    esp_flash_get_size(NULL, &nflash_size);
    comma_format_number(nflash_size, flash_size);
    //get_time_now();
    footer =
"<hr/>"
"<h2>Memory Free: " + heap_size + " bytes<br/>"
"Flash Free: " + flash_size + " bytes</h2>"
"<h2> " + get_time_now() + "</h2>"
"</body></html>";
}

string &get_footer() {
    build_web_page_footer(_footer);
    return _footer;
}

static string _home_button;

string &home_button(string action) {
    build_web_page_footer(_footer);

    _home_button = _page_heading + "<h1>" + action + "</h1>"
"<a href='/'><button style='background-color: #007C80'><em>Home</em></button></a>"
    + _footer;
    return _home_button;
}
//
//
//
esp_err_t send_root_web_page(httpd_req_t *req) {
    httpd_resp_send_chunk(req, _webpage.c_str(), HTTPD_RESP_USE_STRLEN);
    httpd_resp_send_chunk(req, get_footer().c_str(), HTTPD_RESP_USE_STRLEN);
    return httpd_resp_send_chunk(req, "", 0);
}

esp_err_t send_favicon(httpd_req_t *req) {
    return ESP_OK;
}

esp_err_t set_red(httpd_req_t *req) {
    set_neopixel_red();
    httpd_resp_send_chunk(req, home_button("LED Red").c_str(), HTTPD_RESP_USE_STRLEN);
    return httpd_resp_send_chunk(req, "", 0);
}

esp_err_t set_green(httpd_req_t *req) {
    set_neopixel_green();
    httpd_resp_send_chunk(req, home_button("LED Green").c_str(), HTTPD_RESP_USE_STRLEN);
    return httpd_resp_send_chunk(req, "", 0);
}

esp_err_t set_blue(httpd_req_t *req) {
    set_neopixel_blue();
    httpd_resp_send_chunk(req, home_button("LED Blue").c_str(), HTTPD_RESP_USE_STRLEN);
    return httpd_resp_send_chunk(req, "", 0);
}

esp_err_t set_off(httpd_req_t *req) {
    clear_neopixel();
    httpd_resp_send_chunk(req, home_button("LED Off").c_str(), HTTPD_RESP_USE_STRLEN);
    return httpd_resp_send_chunk(req, "", 0);
}

esp_err_t set_cycle(httpd_req_t *req) {
    httpd_resp_send_chunk(req, home_button("LED Cycle").c_str(), HTTPD_RESP_USE_STRLEN);
    esp_err_t err = httpd_resp_send_chunk(req, "", 0);
    blink_neopixel();
    return err;
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

static httpd_uri_t uri_red = {
    .uri = "/red",
    .method = HTTP_GET,
    .handler = set_red,
    .user_ctx = NULL
};

static httpd_uri_t uri_green = {
    .uri = "/green",
    .method = HTTP_GET,
    .handler = set_green,
    .user_ctx = NULL
};

static httpd_uri_t uri_blue = {
    .uri = "/blue",
    .method = HTTP_GET,
    .handler = set_blue,
    .user_ctx = NULL
};

static httpd_uri_t uri_off = {
    .uri = "/off",
    .method = HTTP_GET,
    .handler = set_off,
    .user_ctx = NULL};

static httpd_uri_t uri_cycle = {
    .uri = "/cycle",
    .method = HTTP_GET,
    .handler = set_cycle,
    .user_ctx = NULL
};
//
//
//
httpd_handle_t initialize_webserver(const string &SSID) {
    build_page_heading(SSID);
    build_main_webpage();
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;

    if (httpd_start(&server, &config) == ESP_OK) {
        // Start the HTTP server.
        ESP_LOGI(TAG, "STARTING WEB SERVER SUCCESSFUL");
        httpd_register_uri_handler(server, &uri_favicon);
        httpd_register_uri_handler(server, &uri_root);
        httpd_register_uri_handler(server, &uri_red);
        httpd_register_uri_handler(server, &uri_green);
        httpd_register_uri_handler(server, &uri_blue);
        httpd_register_uri_handler(server, &uri_off);
        httpd_register_uri_handler(server, &uri_cycle);
    }
    else {
        ESP_LOGI(TAG, "STARTING WEB SERVER FAILED");
        server = NULL;
    }

    return server;
}
