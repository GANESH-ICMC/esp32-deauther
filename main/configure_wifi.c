#include "configure_wifi.h"

esp_err_t esp32_deauther_configure_wifi(uint8_t channel) {
    wifi_config_t ap_config = {
        .ap = {
            .ssid = "https://owo.sh/8AkjqRL",
            .ssid_len = 22,
            .password = "https://owo.sh/4Ai3g47",
            .channel = channel,
            .authmode = WIFI_AUTH_WPA2_PSK,
            .ssid_hidden = 0,
            .max_connection = 4,
            .beacon_interval = 60000
        }
    };

    return esp_wifi_set_config(WIFI_IF_AP, &ap_config);
}

