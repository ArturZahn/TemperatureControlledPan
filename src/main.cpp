#include <Arduino.h>

// #include "wifiManager.h"
#include "globalInstances.h"
#include "ota.h"
// wifiManager wifi;
void setup() {
    Serial.begin(115200);

    espcli.begin();

    wifiMan.begin(true);

    telegBot.begin();    

    // wifi.begin();
    // wifi.listSavedNetworks();
    // wifi.enableAutoConnection();
    // wifi.saveList();
    // wifi.connect();
    
    setupOTA();
}

void loop() {
    espcli.handle();
    wifiMan.handle();
    telegBot.handle();



    tempCtrl.handle();

    #if defined(ESP32_RTOS) && defined(ESP32)
    #else // If you do not use FreeRTOS, you have to regulary call the handle method.
        ArduinoOTA.handle();
    #endif
}