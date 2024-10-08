#ifndef ACTUATORSCONTROL_H
#define ACTUATORSCONTROL_H

#include <Arduino.h>
#include "print.h"

class actuatorsControl
{
private:
    bool mixing;
    int mixingPin;
public:
    actuatorsControl(int mixingPin);
    void setMixingState(bool mixingState);
};

#endif