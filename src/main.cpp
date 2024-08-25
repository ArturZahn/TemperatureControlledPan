#include <Arduino.h>

#include "temperatureControl.h"

temperatureControl tempCtrl(TEMP_PROBE_PIN, RELAY_PIN, true);

void setup() {
    Serial.begin(115200);
    tempCtrl.setMaxTemperatureDifference(2.5);
    tempCtrl.start(20);
}

void loop() {
    tempCtrl.handle();
}