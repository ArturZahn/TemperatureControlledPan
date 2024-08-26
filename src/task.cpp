#include "task.h"

task::task()
{
    this->isRunning = false;
    this->finished = false;
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
    this->finished = true;
}

bool task::checkIfIsRunning()
{
    return this->isRunning;
}

bool task::checkIfFinished()
{
    return this->finished;
}