#include <Arduino.h>
#include <vector>
#include <memory>

#include "globalInstances.h"
#include "taskList.h"
#include "wait.h"
#include "heatup.h"


taskList myList;

void setup() {
    Serial.begin(115200);

    tempCtrl.setMaxTemperatureDifference(MAX_TEMPERATURE_DIFFERENCE);
    tempCtrl.start();

    myList.tasks.push_back(make_unique<heatup>(80));
    myList.tasks.push_back(make_unique<wait>(5*60*1000));
    myList.tasks.push_back(make_unique<heatup>(42));
    myList.tasks.push_back(make_unique<wait>(4*60*60*1000));

    myList.runAll();
}


void loop() {
    tempCtrl.handle();
    myList.handle();
}