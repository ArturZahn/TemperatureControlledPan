#include "heatup.h"

heatup::heatup(float targetTemperature)
{
    this->targetTemperature = targetTemperature;
}
void heatup::handleStart()
{
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