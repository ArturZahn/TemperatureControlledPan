#include <Arduino.h>

// #include "wifiManager.h"
#include "globalInstances.h"

// wifiManager wifi;
void setup() {
    Serial.begin(115200);

    espcli.begin();

    // wifi.begin();
    // wifi.listSavedNetworks();
    // wifi.enableAutoConnection();
    // wifi.saveList();
    // wifi.connect();
}

void loop() {
    espcli.handle();
}