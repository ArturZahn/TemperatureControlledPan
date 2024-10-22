#include "heatup.h"

heatup::heatup(float targetTemperature)
{
    this->targetTemperature = targetTemperature;
}
void heatup::handleStart()
{
    myprintln("start at temperature ", this->targetTemperature);
    tempCtrl.start();
    tempCtrl.setTemperatureTarget(this->targetTemperature);
    
}
void heatup::handleForceStop()
{

}
void heatup::handle()
{
    if(tempCtrl.checkIfReachedTarget())
    {
        this->setAsStoped();
    }
}

void heatup::setTargetTemperature(float temperature)
{
    this->targetTemperature = temperature;
}