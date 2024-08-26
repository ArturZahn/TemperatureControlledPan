#include <Arduino.h>
#include <vector>
#include <memory>

#include "globalInstances.h"
#include "taskList.h"
#include "allTasks.h"


taskList myList;

void setup() {
    Serial.begin(115200);

    tempCtrl.setMaxTemperatureDifference(MAX_TEMPERATURE_DIFFERENCE);
    tempCtrl.start();

    myList.tasks.push_back(make_unique<wait>(2*1000));
    myList.tasks.push_back(make_unique<mixing>(true));
    myList.tasks.push_back(make_unique<wait>(4*1000));
    myList.tasks.push_back(make_unique<mixing>(false));
    myList.tasks.push_back(make_unique<heatup>(10));

    myList.runAll();
}


void loop() {
    tempCtrl.handle();
    myList.handle();
}