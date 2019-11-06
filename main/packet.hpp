#pragma once

#include "esp_wifi.h"

typedef uint8_t MacAddr[6];

class PacketSender {
    public:
        esp_err_t deauth(const MacAddr ap, const MacAddr station,
                const MacAddr bssid, uint8_t reason, uint8_t channel) noexcept;
        esp_err_t beacon(const MacAddr mac, const char* ssid,
                uint8_t channel, bool wpa2) noexcept;
        esp_err_t probe(const MacAddr mac, const char* ssid,
                uint8_t channel) noexcept;
        esp_err_t raw(const uint8_t* packet, int32_t len,
                bool en_sys_seq = false) noexcept;
    private:
        esp_err_t change_channel(uint8_t channel) noexcept;
        uint16_t seqnum;
        uint8_t buffer[200];
};
