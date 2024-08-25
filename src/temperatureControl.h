#ifndef TEMPERATURECONTROL_H
#define TEMPERATURECONTROL_H

#include <OneWire.h>
#include <DallasTemperature.h>

#include "config.h"
#include "timedLoop.h"

class temperatureControl
{
private:
    OneWire oneWire;
    DallasTemperature tempProbe;

    float targetTemperature;
    bool controlState;
    uint relayPin;
    bool invertedRalay;
    float maxTemperatureDifference;
    bool reachedTargetTemp;
    bool isHeating;

    timedLoop loop;

    void startHeating();
    void stopHeating();


public:
    temperatureControl(uint _tempPin, uint _relayPin, bool invertedRalay);

    void start();
    void start(float temperature);
    void stop();
    bool getControlState();

    void handle();

    void setMaxTemperatureDifference(float temp);
    void setTemperatureTarget(float temp);
    float getCurrentTemperature();
    bool checkIfReachedTarget();
};



#endif