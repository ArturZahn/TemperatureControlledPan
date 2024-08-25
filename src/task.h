#ifndef TASK_H
#define TASK_H

#include <Arduino.h>

class task {
protected:
    bool isRunning;
    void setAsStoped();
public:
    task();

    void start();
    void forceStop();
    bool checkIfIsRunning();

    virtual void handleStart() = 0;
    virtual void handleForceStop() = 0;
    virtual void handle() = 0;
};

#endif

