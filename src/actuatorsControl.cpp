#include "actuatorsControl.h"


actuatorsControl::actuatorsControl(int mixingPin)
{
    this->mixingPin = mixingPin;

    pinMode(mixingPin, OUTPUT);
}

void actuatorsControl::setMixingState(bool mixingState)
{
    digitalWrite(this->mixingPin, mixingState);
}