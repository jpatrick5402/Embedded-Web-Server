// webServer & general header files
#include "string.h"
#include "stdlib.h"
#include "unistd.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "sys/param.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"
#include "protocol_examples_utils.h"
#include "esp_tls_crypto.h"
#include "esp_http_server.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_tls.h"
#include "esp_check.h"
#include "sys/socket.h"

// GPIO header files
#include "inttypes.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

static const char *TAG = "custom_web_server";

static esp_err_t index_get_handler(httpd_req_t *req)
{
    extern const unsigned char index_start[] asm("_binary_index_html_start"); // getting html data
    extern const unsigned char index_end[]   asm("_binary_index_html_end");
    const size_t index_size = (index_end - index_start);

    httpd_resp_send(req, (const char *)index_start, index_size); // sending html over

    // getting client IP address
    int sockfd = httpd_req_to_sockfd(req);
    char ipstr[INET6_ADDRSTRLEN];
    struct sockaddr_in6 addr;
    socklen_t addr_size = sizeof(addr);
    if (getpeername(sockfd, (struct sockaddr *)&addr, &addr_size) < 0) {
        ESP_LOGE(TAG, "Error getting client IP");
        return ESP_OK;
    }
    inet_ntop(AF_INET, &addr.sin6_addr.un.u32_addr[3], ipstr, sizeof(ipstr));
    ESP_LOGI(TAG, "Client IP => %s", ipstr);

    // triggering pin 18 to turn on, wait, and turn off when someone connects
    gpio_set_level(18, 1);
    sleep(1);
    gpio_set_level(18, 0);

    return ESP_OK;
}

static esp_err_t favicon_get_handler(httpd_req_t *req)
{
    extern const unsigned char favicon_ico_start[] asm("_binary_favicon_ico_start");
    extern const unsigned char favicon_ico_end[]   asm("_binary_favicon_ico_end");
    const size_t favicon_ico_size = (favicon_ico_end - favicon_ico_start);
    httpd_resp_set_type(req, "image/x-icon");
    httpd_resp_send(req, (const char *)favicon_ico_start, favicon_ico_size); // sending data over
    return ESP_OK;
}

static const httpd_uri_t homepage = {
    .uri = "/index.html",
    .method = HTTP_GET,
    .handler = index_get_handler, // goes to index_get_handler()
    .user_ctx = NULL
};

static const httpd_uri_t favicon = {
    .uri = "/favicon.ico",
    .method = HTTP_GET,
    .handler = favicon_get_handler, // goes to favicon_get_handler()
    .user_ctx = NULL
};

static httpd_handle_t start_webserver(void) // starting function for server
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        // Set URI handlers
        ESP_LOGI(TAG, "Registering URI handlers");
        httpd_register_uri_handler(server, &homepage); // goes to httpd_uri_t index
        httpd_register_uri_handler(server, &favicon); // goes to httpd_uri_t index
        ESP_LOGI(TAG, "All URI handlers registered");
        return server;
    }

    ESP_LOGI(TAG, "Error starting server!");
    return NULL;
}

void app_main(void) { // entry point for our application
 
    static httpd_handle_t server = NULL;
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(example_connect());
    server = start_webserver(); // goes to start_webserver() function
    ESP_LOGI(TAG, "Waiting for connections");

    // GPIO configuration
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = 18;
    io_conf.pin_bit_mask = (1ULL << 18);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    
    while (server) {
        sleep(5);
    }
}
