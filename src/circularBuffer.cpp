#include "circularBuffer.h"



circularBuffer::circularBuffer(int size)
{
    bufferSize = size;
    cBuffer = (char*) malloc(bufferSize*sizeof(char));
    bufferStart = cBuffer;
    bufferEnd = cBuffer;
    isBufferFull = false;
}

circularBuffer::~circularBuffer()
{
    free(cBuffer);
}

void circularBuffer::addToBuffer(String str)
{
    if(str.length()==0) return;

    char* newBufferEnd;
    if(bufferEnd+str.length() <= cBuffer+bufferSize) // fits before end of buffer
    {
        strncpy(bufferEnd, str.c_str(), str.length());

        newBufferEnd = bufferEnd+str.length();
        if(newBufferEnd == cBuffer+bufferSize)
            newBufferEnd -= bufferSize;

        if(isBufferFull || (bufferEnd<bufferStart && (newBufferEnd>bufferStart || newBufferEnd == cBuffer)))
        {
            bufferStart = newBufferEnd;
        }
    }
    else if(str.length() < bufferSize) // doesnt fit before end of buffer
    {
        // data will be splited, de beginning will be written to the end of the buffer, and the rest an the beginning of the buffer

        // write first part
        int firstLength = cBuffer+bufferSize-bufferEnd;
        if(firstLength > 0) strncpy(bufferEnd, str.c_str(), firstLength);

        // write last part
        int lastPartLength = str.length()-firstLength;
        strncpy(cBuffer, str.c_str()+firstLength, lastPartLength);

        // update indexes
        newBufferEnd = cBuffer+lastPartLength;

        if(isBufferFull || bufferStart>bufferEnd || newBufferEnd > bufferStart)
        {
            bufferStart = newBufferEnd;
        }
    }
    else // str is larger or equal the buffer size
    {
        int newStrStart = str.length()-bufferSize;
        strncpy(cBuffer, str.c_str()+newStrStart, bufferSize);
        newBufferEnd = cBuffer;
        bufferStart = cBuffer;
    }
    
    bufferEnd = newBufferEnd;
    if(bufferEnd == bufferStart)
        isBufferFull = true;
}

String circularBuffer::getBufferAsString()
{
    int strSize = isBufferFull ? bufferSize : bufferEnd - bufferStart;
    if (strSize < 0)
        strSize += bufferSize;

    if (strSize == 0)
        return "";

    String str;
    str.reserve(strSize);

    int index = bufferStart - cBuffer;
    if (index < 0)
        index += bufferSize;

    for (int i = 0; i < strSize; i++)
    {
        str += cBuffer[index];
        index = (index + 1) % bufferSize;
    }

    return str;
}