#include "temperatureControl.h"

temperatureControl::temperatureControl(uint tempPin, uint _relayPin, bool _invertedRalay)
  : oneWire(tempPin),
    tempProbe(&oneWire),
    loop(tempCheckPeriod)
{
    this->targetTemperature = 0;
    this->controlState = false;
    this->reachedTargetTemp = false;
    this->isHeating = false;

    this->relayPin = _relayPin;
    this->invertedRalay = _invertedRalay;

    pinMode(relayPin, OUTPUT);
}

// starts and stops the temperature control
void temperatureControl::start()
{
    this->controlState = true;
}
void temperatureControl::start(float temp)
{
    this->start();
    this->setTemperatureTarget(temp);
}
void temperatureControl::stop()
{
    this->controlState = false;
    this->reachedTargetTemp = false;
    this->stopHeating();
}

bool temperatureControl::getControlState()
{
    return this->controlState;
}

void temperatureControl::startHeating()
{
    this->isHeating = true;
    digitalWrite(this->relayPin, !this->invertedRalay);
    Serial.println("ON");
}
void temperatureControl::stopHeating()
{
    this->isHeating = false;
    digitalWrite(this->relayPin, this->invertedRalay);
    Serial.println("OFF");
}

void temperatureControl::setMaxTemperatureDifference(float temp)
{
    this->maxTemperatureDifference = temp;
}
void temperatureControl::setTemperatureTarget(float temp)
{
    this->reachedTargetTemp = false;
    this->targetTemperature = temp;
}
float temperatureControl::getCurrentTemperature()
{
    tempProbe.requestTemperatures(); 
    return tempProbe.getTempCByIndex(0);
}

bool temperatureControl::checkIfReachedTarget()
{
    return this->reachedTargetTemp;
}


void temperatureControl::handle()
{
    if(loop.check())
    {
        if(this->controlState)
        {
            if(this->isHeating && this->getCurrentTemperature() >= this->targetTemperature)
            {
                this->stopHeating();
                this->reachedTargetTemp = true;
            }

            if(!this->isHeating && (this->getCurrentTemperature() <= (this->targetTemperature - this->maxTemperatureDifference)))
            {
                this->startHeating();
            }
        }
    }
}
