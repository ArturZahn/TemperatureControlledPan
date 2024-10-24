#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <Arduino.h>

class circularBuffer
{
private:
    int bufferSize;
    char* cBuffer;
    char* bufferStart;
    char* bufferEnd;
    bool isBufferFull;

public:
    circularBuffer(int size);
    ~circularBuffer();

    void addToBuffer(String str);
    String getBufferAsString();
    String readBuffer();
    void clearBuffer();
    int getLength();
};


#endif