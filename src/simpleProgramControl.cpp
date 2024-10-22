#include "simpleProgramControl.h"

#include "globalInstances.h"

simpleProgramControl simpleProgramCtrl(1);

simpleProgramControl::simpleProgramControl(int n) :
myheatup(0),
mywait(0),
sendFinishedLoop(10*1000),
sendFeedBackLoop(10*1000)
{
}


void simpleProgramControl::setTemperature(float temp)
{
    myheatup.setTargetTemperature(temp);
}
void simpleProgramControl::setTime(unsigned long time)
{
    mywait.setTime(time);
}

void simpleProgramControl::start()
{
    if(stage == stageWaitingStart)
    {
        stage = stageHeatingUp;
        myheatup.start();
    }
}

void simpleProgramControl::reset()
{
    stage == stageWaitingStart;
    myheatup.forceStop();
    mywait.forceStop();
    tempCtrl.stop();
}

String getStageName(simpleProgramControlStages stage)
{
    switch (stage)
    {
        case stageWaitingStart: return "stageWaitingStart";
        case stageHeatingUp: return "stageHeatingUp";
        case stageTime: return "stageTime";
        case stageFinished: return "stageFinished";
        default: return "Unknown Stage";
    }
}

void simpleProgramControl::handle()
{
    switch (stage)
    {
    case stageHeatingUp:
        myheatup.handle();
        if(myheatup.checkIfFinished())
        {
            stage = stageTime;
            mywait.start();
        }
        break;

    case stageTime:
        mywait.handle();
        if(mywait.checkIfFinished())
        {
            stage = stageFinished;
            tempCtrl.stop();
        }
        break;

    case stageFinished:
            if(sendFinishedLoop.check())
            {
                myprintln("Finished");
            }
        break;
    
    default:
        break;
    }

    if(sendFeedBackLoop.check())
    {
        myprintln("Stage: ", getStageName(stage));
        myprintln("Temp: ", tempCtrl.getCurrentTemperature(), "°C");
    }
}