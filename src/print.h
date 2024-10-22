#ifndef PRINT_H
#define PRINT_H

#include <Arduino.h>

#include "config.h"
#include "circularBuffer.h"

class myprintClass
{
private:
public:
    circularBuffer printBuffer;
    myprintClass();
    void addToBuffer(String str);
};

extern myprintClass myprintObj;

template<typename T>
void myprint(T t) {
    Serial.print(t);
    myprintObj.printBuffer.addToBuffer(String(t));
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
