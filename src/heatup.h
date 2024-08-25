#ifndef HEATUP_H
#define HEATUP_H

#include "task.h"
#include "globalInstances.h"

class heatup : public task {
private:
    float targetTemperature;
public:
    heatup(float targetTemperature);
    void handleStart() override;
    void handleForceStop() override;
    void handle() override;
};

#endif