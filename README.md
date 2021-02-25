# ESP32 Deauther

(Maybe) Port of https://github.com/spacehuhn/esp8266_deauther to the ESP32,
based on the `esp_wifi_80211_tx` function described in https://github.com/Jeija/esp32-80211-tx

# How does this work
In compiled [ESP32 WiFi Stack libraries](https://github.com/espressif/esp32-wifi-lib) there is a function `ieee80211_raw_frame_sanity_check` that blocks some types of raw 802.11 frames from being sent. Using `zmuldefs` linker flag during compilation (see `main/CMakeLists.txt`) this function from WiFi Stack librabries can be overriden to always return `0` which leads to unrestricted raw frame transmission.

# Building

Install [esp-idf](https://github.com/espressif/esp-idf). This project is built and tested with
commit 5ef1b390026270503634ac3ec9f1ec2e364e23b2.

Build project as usual using `idf.py build`.

Built with v4.1-dev-763-ga45e99853

# Flashing

`idf.py flash`
