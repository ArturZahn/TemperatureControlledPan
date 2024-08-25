#ifndef WAIT_H
#define WAIT_H

#include "task.h"


class wait : public task {
private:
    unsigned long delay;
    unsigned long startTime;
public:
    wait(unsigned long delay);
    void handleStart() override;
    void handleForceStop() override;
    void handle() override;
};

#endif