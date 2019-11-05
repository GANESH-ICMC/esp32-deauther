extern "C" {
#include "freertos/FreeRTOS.h"

#include "esp_system.h"
#include "esp_event.h"
#include "esp_wifi.h"

#include "nvs_flash.h"

#include "configure_wifi.h"
}

#include "packet.hpp"

const char *rick_ssids[] = {
	"01 Never gonna give you up",
	"02 Never gonna let you down",
	"03 Never gonna run around",
	"04 and desert you",
	"05 Never gonna make you cry",
	"06 Never gonna say goodbye",
	"07 Never gonna tell a lie",
	"08 and hurt you"
};
#define TOTAL_LINES (sizeof(rick_ssids) / sizeof(char *))

void spam_task(void *pvParameter) {
    PacketSender sender;
    uint8_t line = 0;

    uint8_t mac[6] = {0};
    for(int i = 0; i < 5; i++) mac[i] = rick_ssids[i][8];

	while(1) {
        vTaskDelay(100 / TOTAL_LINES / portTICK_PERIOD_MS);

        //change mac address
		mac[5]++;
        sender.beacon(mac, rick_ssids[line], 1, true);

        if(++line >= TOTAL_LINES) {
            line = 0;
        }
    }
}

extern "C" void app_main(void) {
    nvs_flash_init();
    tcpip_adapter_init();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));

    // Init dummy AP to specify a channel and get WiFi hardware into
    // a mode where we can send the actual fake beacon frames.
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));

    ESP_ERROR_CHECK(esp32_deauther_configure_wifi(/* channel */ 1));

    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_set_ps(WIFI_PS_NONE));

    xTaskCreate(&spam_task, "spam_task", 2048, NULL, 5, NULL);
}

