#include "print.h"
#include "globalInstances.h"

myprintClass myprintObj;

myprintClass::myprintClass()
{
}

void myprintClass::begin()
{
    printBuffer = (char*) malloc(printBufferSize*sizeof(char));
    bufferStart = printBuffer;
    bufferEnd = printBuffer;
    isBufferFull = false;
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
        printBuffer[i] = '#';
    
    int i = start;
    for (int count = 0; count < currentLength; count++)
    {
        printBuffer[i] = 'a'+count;
        answer += printBuffer[i];
        i++;
        if(i >= printBufferSize) i = 0;
    }

    String addStr = "";
    for (int j = 0; j < addLength; j++)
    {
        addStr += String(j);
    }
    answer += addStr;

    
    bufferStart = printBuffer+start;

    bufferEnd = printBuffer+start+currentLength;
    if(bufferEnd>printBuffer+printBufferSize)
        bufferEnd -= printBufferSize;

    isBufferFull = (currentLength == printBufferSize);

    // print test data
    for (int i = 0; i < printBufferSize; i++)
    {
        testPrintStr += printBuffer[i];
    }
    testPrintStr += "  ";

    char bufferASDASDASDhienobnjot[1000];
    snprintf(bufferASDASDASDhienobnjot, sizeof(bufferASDASDASDhienobnjot), "%20s %4d %4d %4d  ", addStr, int(bufferStart-printBuffer), int(bufferEnd-printBuffer), isBufferFull);

    addToBuffer(addStr);
    
    for (int i = 0; i < printBufferSize; i++)
    {
        testPrintStr += printBuffer[i];
    }
    testPrintStr += "  ";
    
    testPrintStr += bufferASDASDASDhienobnjot;
    snprintf(bufferASDASDASDhienobnjot, sizeof(bufferASDASDASDhienobnjot), "%4d %4d %4d   ", int(bufferStart-printBuffer), int(bufferEnd-printBuffer), isBufferFull);
    testPrintStr += bufferASDASDASDhienobnjot;

    String got = getBufferAsString();
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

void myprintClass::addToBuffer(String str)
{
    if(str.length()==0)
    {
        testPrintStr == " -  ";
        return;
    }

    if(bufferEnd+str.length() <= printBuffer+printBufferSize) // fits before end of buffer
    {
        testPrintStr == " A";
        strncpy(bufferEnd, str.c_str(), str.length());

        char* newBufferEnd = bufferEnd+str.length();
        if(newBufferEnd == printBuffer+printBufferSize)
            newBufferEnd -= printBufferSize;

        if(isBufferFull) // if buffer full
        {
            testPrintStr == "1 ";
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
                    testPrintStr == "2 ";
                }
                else
                {
                    if(newBufferEnd == printBuffer)
                    {
                        bufferStart = newBufferEnd;
                        testPrintStr == "3 ";
                    }
                    else
                    {
                        testPrintStr == "4 ";
                    }
                }
            }
            else
            {
                testPrintStr == "5 ";
            }
        }

        bufferEnd = newBufferEnd;

        if(bufferEnd == bufferStart)
            isBufferFull = true;
    }
    else if(str.length() < printBufferSize) // doesnt fit before end of buffer
    {
        testPrintStr == " B  ";
        // first part
        int firstLength = printBuffer+printBufferSize-bufferEnd;
        if(firstLength > 0) strncpy(bufferEnd, str.c_str(), firstLength);

        // last part
        int lastPartLength = str.length()-firstLength;
        strncpy(printBuffer, str.c_str()+firstLength, lastPartLength);

        char* newBufferEnd = printBuffer+lastPartLength;

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
        testPrintStr == " C  ";
        int newStrStart = str.length()-printBufferSize;
        strncpy(printBuffer, str.c_str()+newStrStart, printBufferSize);
        bufferStart = printBuffer;
        bufferEnd = printBuffer;
        isBufferFull = true;
    }
}


String myprintClass::getBufferAsString()
{
    int strSize = isBufferFull ? printBufferSize : bufferEnd-bufferStart;
    if(strSize < 0)
        strSize += printBufferSize;

    String str;
    if (isBufferFull && bufferStart == printBuffer)
    {
        // Create a String from the buffer
        str = String(printBuffer, printBufferSize);
    }
    else
    {   
        str = "";
        int i = (int)(bufferStart-printBuffer);
        for (int count = 0; count < strSize; count++)
        {
            str += printBuffer[i];
            i++;
            if(i>=printBufferSize) i = 0;
        }
        

        // // For non-full buffer, handle potential wrap-around
        // char tempBuffer[strSize + 1]; // +1 for null terminator
        // int index = 0;

        // for (int i = (int)(bufferStart-printBuffer); i != (int)(bufferEnd-printBuffer); i = (i + 1) % printBufferSize) {
        //     tempBuffer[index++] = printBuffer[i];
        // }

        // tempBuffer[strSize] = '\0'; // Null-terminate the string

        // str = String(tempBuffer);
    }

    return str;
    
}