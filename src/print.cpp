#include "print.h"
#include "globalInstances.h"

myprintClass myprintObj;

myprintClass::myprintClass() :
myCircularBuffer(printBufferSize)
{
}

void myprintClass::begin()
{
}

String testPrintStr;
bool okStatus;
int okCount;
void myprintClass::testAll()
{   
    okCount = 0;
    int count = 0;
    int total = printBufferSize*(printBufferSize+1)*(printBufferSize+3);
    for (int start = 0; start < printBufferSize; start++)
    {
        for (int currentLength = 0; currentLength <= printBufferSize; currentLength++)
        {
            for (int addLength = 0; addLength <= printBufferSize+2; addLength++)
            {
                count++;
                testPrintStr = "";
                okStatus = false;
                test(start, currentLength, addLength);
                if (!okStatus)
                {
                    myprint(testPrintStr);
                }

                if(count%100 == 0)
                {
                    myprintln(okCount, "/", count, "/", total);
                }
                
            }
        }
        if(count%100 != 0)
        {
            myprintln(okCount, "/", count, "/", total);
        }
    }
}

String getLastFiveCharacters(String input) {
    int len = input.length();  // Get the length of the string

    if (len <= printBufferSize) {
        return input;  // If the string has printBufferSize or fewer characters, return it as is
    } else {
        return input.substring(len - printBufferSize);  // Return the last printBufferSize characters
    }
}

void myprintClass::test(int start, int currentLength, int addLength)
{
    
    String answer = "";
    for (int i = 0; i < printBufferSize; i++)
        myCircularBuffer.printBuffer[i] = '#';
    
    int i = start;
    for (int count = 0; count < currentLength; count++)
    {
        myCircularBuffer.printBuffer[i] = 'a'+count;
        answer += myCircularBuffer.printBuffer[i];
        i++;
        if(i >= printBufferSize) i = 0;
    }

    String addStr = "";
    for (int j = 0; j < addLength; j++)
    {
        addStr += String(j);
    }
    answer += addStr;

    
    myCircularBuffer.bufferStart = myCircularBuffer.printBuffer+start;

    myCircularBuffer.bufferEnd = myCircularBuffer.printBuffer+start+currentLength;
    if(myCircularBuffer.bufferEnd>myCircularBuffer.printBuffer+printBufferSize)
        myCircularBuffer.bufferEnd -= printBufferSize;

    myCircularBuffer.isBufferFull = (currentLength == printBufferSize);

    // print test data
    for (int i = 0; i < printBufferSize; i++)
    {
        testPrintStr += myCircularBuffer.printBuffer[i];
    }
    testPrintStr += "  ";

    char bufferASDASDASDhienobnjot[1000];
    snprintf(bufferASDASDASDhienobnjot, sizeof(bufferASDASDASDhienobnjot), "%20s %4d %4d %4d  ", addStr, int(myCircularBuffer.bufferStart-myCircularBuffer.printBuffer), int(myCircularBuffer.bufferEnd-myCircularBuffer.printBuffer), myCircularBuffer.isBufferFull);

    myCircularBuffer.addToBuffer(addStr);
    
    for (int i = 0; i < printBufferSize; i++)
    {
        testPrintStr += myCircularBuffer.printBuffer[i];
    }
    testPrintStr += "  ";
    
    testPrintStr += bufferASDASDASDhienobnjot;
    snprintf(bufferASDASDASDhienobnjot, sizeof(bufferASDASDASDhienobnjot), "%4d %4d %4d   ", int(myCircularBuffer.bufferStart-myCircularBuffer.printBuffer), int(myCircularBuffer.bufferEnd-myCircularBuffer.printBuffer), myCircularBuffer.isBufferFull);
    testPrintStr += bufferASDASDASDhienobnjot;

    String got = myCircularBuffer.getBufferAsString();
    answer = getLastFiveCharacters(answer);

    snprintf(bufferASDASDASDhienobnjot, sizeof(bufferASDASDASDhienobnjot), "%20s %20s ", got, answer);
    testPrintStr += bufferASDASDASDhienobnjot;

    if(got == answer)
    {
        testPrintStr += "OK\n";
        okStatus = true;
        okCount++;
    }
    else testPrintStr += "Fail\n";
}