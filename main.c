#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"

#include "driver/gpio.h"
#include "hal/touch_sensor_hal.h"
#include "esp_http_client.h"
#include "esp_interface.h"

#define REED_SWITCH_GPIO 18

void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        esp_wifi_connect();
    }
}

void gpio_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    if ((int) event_base == GPIO_INTR_LOW_LEVEL) {
        esp_http_client_config_t config = {
                .url = "[URL]",
                .method = HTTP_METHOD_POST,
        };
        esp_http_client_handle_t client = esp_http_client_init(&config);
        esp_http_client_perform(client);
        esp_http_client_cleanup(client);
    }
}

void app_main(void)
{
    nvs_flash_init();
    esp_netif_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT() ;
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &wifi_event_handler, NULL);

    wifi_config_t wifi_config = {
            .sta = {
                    .ssid = "[SSID]",
                    .password = "[PASSWORD]",
            },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config((wifi_interface_t) ESP_IF_WIFI_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_ERROR_CHECK(esp_wifi_connect());

    gpio_config_t io_conf = {
            .intr_type = GPIO_INTR_LOW_LEVEL,
            .pin_bit_mask = (1ULL<<REED_SWITCH_GPIO),
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = true,
            .pull_down_en = false,
    };

    gpio_config(&io_conf);
    esp_event_handler_register((esp_event_base_t) GPIO_INTR_LOW_LEVEL, GPIO_INTR_LOW_LEVEL, &gpio_event_handler, NULL);
}