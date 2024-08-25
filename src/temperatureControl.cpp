#include "temperatureControl.h"

#ifdef simulateTemperature
float devSimulatedTemperature = 24;
timedLoop devTemperatureLoop(100);
#endif

#ifdef tempPrintPeriod
timedLoop devPrintTemp(tempPrintPeriod);
#endif

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
}
void temperatureControl::stopHeating()
{
    this->isHeating = false;
    digitalWrite(this->relayPin, this->invertedRalay);
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
    #ifndef simulateTemperature
    tempProbe.requestTemperatures(); 
    return tempProbe.getTempCByIndex(0);
    #else
    return devSimulatedTemperature;
    #endif
}

bool temperatureControl::checkIfReachedTarget()
{
    return this->reachedTargetTemp;
}


void temperatureControl::handle()
{
    
    #ifdef simulateTemperature
    if(devTemperatureLoop.check())
    {
        if(this->isHeating) devSimulatedTemperature += 0.1;
        else devSimulatedTemperature -= 0.1;
    }
    #endif

    
    #ifdef tempPrintPeriod
    if(devPrintTemp.check())
    {
        Serial.print("Temp: ");
        Serial.print(this->getCurrentTemperature());
        Serial.println("°C");
    }
    #endif

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
