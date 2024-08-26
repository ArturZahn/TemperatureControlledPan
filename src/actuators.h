#ifndef ACTUATORS_H
#define ACTUATORS_H

class actuators
{
private:
    bool mixing;

    int mixingPin;
public:
    actuators(int mixingPin);
    void setMixingState(bool mixingState);
};

#endif