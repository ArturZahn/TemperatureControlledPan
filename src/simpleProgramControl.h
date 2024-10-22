#ifndef SIMPLEPROGRAMCONTROL_H
#define SIMPLEPROGRAMCONTROL_H

#include "heatup.h"
#include "wait.h"
#include "timedLoop.h"

enum simpleProgramControlStages
{
    stageWaitingStart,
    stageHeatingUp,
    stageTime,
    stageFinished
};

class simpleProgramControl
{
private:
    heatup myheatup;
    wait mywait;
    simpleProgramControlStages stage;
    timedLoop sendFinishedLoop;
    timedLoop sendFeedBackLoop;
public:
    simpleProgramControl(int n);
    void setTemperature(float temp);
    void setTime(unsigned long time);
    void start();
    void reset();
    void handle();
};

extern simpleProgramControl simpleProgramCtrl;


#endif