#ifndef PRINT_H
#define PRINT_H

#include <Arduino.h>

#include "config.h"


class myprintClass
{
private:
    char* printBuffer;
    char* bufferStart;
    char* bufferEnd;
    bool isBufferFull;
public:
    myprintClass();
    void begin();
    void testAll();
    void test(int start, int currentLength, int addLength);
    void addToBuffer(String str);
    String getBufferAsString();
};

extern myprintClass myprintObj;

template<typename T>
void myprint(T t) {
    Serial.print(t);
    // myprintObj.addToBuffer(String(t));
}

template<typename T, typename... Args>
void myprint(T first, Args... args) {
    myprint(first);
    myprint(args...);
}

template<typename T>
void myprintln(T t) {
    myprint(t, '\n');
}

template<typename T, typename... Args>
void myprintln(T first, Args... args) {
    myprint(first, args..., '\n');
}

#endif
