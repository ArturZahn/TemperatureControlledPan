#include <Arduino.h>

// #include "wifiManager.h"
#include "globalInstances.h"
#include "ota.h"
#include "print.h"
#include "simpleProgramControl.h"

// wifiManager wifi;
void setup() {
    Serial.begin(115200);
    espcli.begin();
    wifiMan.begin(true);
    telegBot.begin();    

    setupOTA();
}

void loop() {
    espcli.handle();
    wifiMan.handle();
    tempCtrl.handle();
    telegBot.handle();
    simpleProgramCtrl.handle();

    #if defined(ESP32_RTOS) && defined(ESP32)
    #else // If you do not use FreeRTOS, you have to regulary call the handle method.
        ArduinoOTA.handle();
    #endif
}