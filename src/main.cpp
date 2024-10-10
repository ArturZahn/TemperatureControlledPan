#include <Arduino.h>

// #include "wifiManager.h"
#include "globalInstances.h"
#include "ota.h"
#include "print.h"

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

bool waitingForConnection = true;
void loop() {
    espcli.handle();
    wifiMan.handle();
    telegBot.handle();



    tempCtrl.handle();
    // tempCtrl.start(50);

    if(waitingForConnection)
    {
        if(WiFi.status() == WL_CONNECTED)
        {
            waitingForConnection = false;
            myprintObj.testAll();
        }
    }


    #if defined(ESP32_RTOS) && defined(ESP32)
    #else // If you do not use FreeRTOS, you have to regulary call the handle method.
        ArduinoOTA.handle();
    #endif
}