#include "print.h"
#include "globalInstances.h"

myprintClass myprintObj;

myprintClass::myprintClass() :
printBuffer(printBufferSize)
{
}