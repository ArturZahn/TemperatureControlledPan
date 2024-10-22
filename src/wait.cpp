#include "wait.h"

wait::wait(unsigned long delay){
    this->delay = delay;
}
void wait::handleStart(){
    this->startTime = millis();
}
void wait::handleForceStop(){
    
}
void wait::handle(){
    if(millis() - this->startTime >= this->delay)
    {
        this->setAsStoped();
    }
}
void wait::setTime(unsigned long time)
{
    this->delay = time;
}