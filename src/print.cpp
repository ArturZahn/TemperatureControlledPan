#include "print.h"
#include "globalInstances.h"

myprintClass myprintObj;

myprintClass::myprintClass()
{
}

void myprintClass::begin()
{
    buffer = (char*) malloc(printBufferSize*sizeof(char));
    bufferStart = buffer;
    bufferEnd = buffer;
    isBufferFull = false;
}

void myprintClass::testAll()
{
    String outputStr = "";

    for (int start = 0; start < printBufferSize; start++)
    {
        for (int currentLength = 0; currentLength < printBufferSize; currentLength++)
        {
            for (int addLength = 0; addLength < printBufferSize+2; addLength++)
            {
                test(start, currentLength, addLength, outputStr);
            }
        }
    }
    
    telegBot.sendText(outputStr);
}

void myprintClass::test(int start, int currentLength, int addLength, String& outputStr)
{
    for (int i = 0; i < printBufferSize; i++)
        buffer[i] = '#';
    
    int i = start;
    for (int count = 0; count < currentLength; count++)
    {
        buffer[i] = 'a'+count;
    }

    String addStr = "";
    for (int j = 0; j < addLength; j++)
    {
        addStr += String(j);
    }

    // print test data
    for (int i = 0; i < printBufferSize; i++)
        outputStr += buffer[i];
    outputStr += " ";
    outputStr += addStr;
    outputStr += '\n';
}

void myprintClass::addToBuffer(String str)
{
    if(str.length()==0) return;

    if(bufferEnd+str.length() <= buffer+printBufferSize) // fits before end of buffer
    {
        strcpy(bufferEnd, str.c_str());

        char* newBufferEnd = bufferEnd+str.length();

        if(isBufferFull) // if buffer full
        {
            // it will always eat the beginning
            bufferStart = newBufferEnd;
        }
        else // if buffer not full
        {
            if(bufferEnd<bufferStart) // can eat beginning of buffer
            {
                if(newBufferEnd>bufferStart) // ate beginning of buffer
                {
                    bufferStart = newBufferEnd;
                }
            }
        }

        bufferEnd = newBufferEnd;

        if(bufferEnd == bufferStart)
            isBufferFull = true;
    }
    else if(str.length() < printBufferSize) // doesnt fit before end of buffer
    {
        // first part
        int firstLength = buffer+printBufferSize-bufferEnd;
        if(firstLength > 0) strncpy(bufferEnd, str.c_str(), firstLength);

        // last part
        int lastPartLength = str.length()-firstLength;
        strncpy(buffer, str.c_str()+firstLength, lastPartLength);

        char* newBufferEnd = buffer+lastPartLength;

        if(isBufferFull) // if buffer full
        {
            // it will always eat the beginning
            bufferStart = newBufferEnd;
        }
        else // if buffer not full
        {
            if(bufferStart>bufferEnd) // if beginning is after the end
            {
                bufferStart = newBufferEnd; // it will eat
            }
            else if(newBufferEnd > bufferStart)
            {
                bufferStart = newBufferEnd; // it will eat
            }
        }

        bufferEnd = newBufferEnd;
        if(bufferEnd == bufferStart)
            isBufferFull = true;
    }
    else // str is larger or equal the buffer size
    {
        int newStrStart = str.length()-printBufferSize;
        strncpy(buffer, str.c_str()+newStrStart, printBufferSize);
        bufferStart = buffer;
        bufferEnd = buffer+printBufferSize;
        isBufferFull = true;
    }
}