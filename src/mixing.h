#ifndef MIXING_H
#define MIXING_H

#include "task.h"
#include "globalInstances.h"

class mixing : public task {
private:
    bool mixingState;
public:
    mixing(bool mixingState);
    void handleStart() override;
    void handleForceStop() override;
    void handle() override;
};


#endif