#ifndef TIMEDLOOP
#define TIMEDLOOP

#include <Arduino.h>
#include "print.h"

class timedLoop
{
private:
    unsigned long lastRun;
    unsigned int interval;
    
public:
    timedLoop(unsigned int interval);
    bool check();
    unsigned long getLastRunTime();
};


#endif