#ifndef TASK_H
#define TASK_H

#include <Arduino.h>
#include "print.h"

class task {
protected:
    bool isRunning;
    bool finished;
    void setAsStoped();
public:
    task();

    void start();
    void forceStop();
    bool checkIfIsRunning();
    bool checkIfFinished();

    virtual void handleStart() = 0;
    virtual void handleForceStop() = 0;
    virtual void handle() = 0;
};

#endif

