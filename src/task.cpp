#include "task.h"

task::task()
{
    this->isRunning = false;
}

void task::start(){
    if(this->isRunning) this->handleForceStop();

    this->handleStart();
    this->isRunning = true;
}

void task::forceStop(){
    if(!this->isRunning) return;

    this->isRunning = false;
    this->handleForceStop();
}

void task::setAsStoped()
{
    this->isRunning = false;
}

bool task::checkIfIsRunning()
{
    return this->isRunning;
}