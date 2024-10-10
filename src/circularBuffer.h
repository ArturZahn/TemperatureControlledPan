#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <Arduino.h>

class circularBuffer
{
private:
    int bufferSize;
    char* printBuffer;
    char* bufferStart;
    char* bufferEnd;
    bool isBufferFull;
    
public:
    circularBuffer(int size);
    ~circularBuffer();

    void addToBuffer(String str);
    String getBufferAsString();
};


#endif