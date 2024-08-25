#include <Arduino.h>

#include "globalInstances.h"
#include "wait.h"
#include "heatup.h"

heatup heatup1(30);

void setup() {
    Serial.begin(115200);

    tempCtrl.setMaxTemperatureDifference(MAX_TEMPERATURE_DIFFERENCE);
    tempCtrl.start();
}

void loop() {
    tempCtrl.handle();

}