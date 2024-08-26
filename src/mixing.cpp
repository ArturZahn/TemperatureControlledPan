#include "mixing.h"

mixing::mixing(bool mixingState)
{
    this->mixingState = mixingState;
}
void mixing::handleStart()
{
    
    this->setAsStoped();
}
void mixing::handleForceStop()
{
    return;
}
void mixing::handle()
{
    return;
}