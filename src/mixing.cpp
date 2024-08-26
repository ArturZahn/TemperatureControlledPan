#include "mixing.h"

mixing::mixing(bool mixingState)
{
    this->mixingState = mixingState;
}
void mixing::handleStart()
{
    actuatorsCtrl.setMixingState(this->mixingState);
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