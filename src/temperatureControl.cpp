#include "temperatureControl.h"

#define ledPin 22

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
    this->maxTemperatureDifference = MAX_TEMPERATURE_DIFFERENCE;

    this->relayPin = _relayPin;
    this->invertedRalay = _invertedRalay;

    pinMode(relayPin, OUTPUT);
    pinMode(ledPin, OUTPUT);
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
    myprintln("startHeating");
}
void temperatureControl::stopHeating()
{
    this->isHeating = false;
    digitalWrite(this->relayPin, this->invertedRalay);
    myprintln("stopHeating");
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

bool sttLed = false;
void temperatureControl::handle()
{
    #ifdef tempPrintPeriod
    if(devPrintTemp.check())
    {
        myprintln("Temp: ");
        myprintln(this->getCurrentTemperature());
        myprintln("°C");
    }
    #endif
    
    #ifdef simulateTemperature
    if(devTemperatureLoop.check())
    {
        if(this->isHeating) devSimulatedTemperature += 0.1;
        else devSimulatedTemperature -= 0.1;
    }
    #endif

    if(loop.check())
    {
        if(this->controlState)
        {
            float currentTemperature = this->getCurrentTemperature();
            if (currentTemperature > 0)
            {
                if(this->isHeating && currentTemperature >= this->targetTemperature)
                {
                    this->stopHeating();
                    this->reachedTargetTemp = true;
                }

                if(!this->isHeating && (currentTemperature <= (this->targetTemperature - this->maxTemperatureDifference)))
                {
                    this->startHeating();
                }
            }
            else
            {
                myprintln("Erro, temperatura é ");
                myprintln(currentTemperature);
                digitalWrite(ledPin, sttLed);
                sttLed = !sttLed;
            }
        }
    }
}
