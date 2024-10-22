#ifndef CONFIG_H
#define CONFIG_H



#if __has_include("privateConfig.h")
#else
    #error "Error: 'privateConfig.h' file not found. Please take a look at file 'privateConfig_template.h'"
#endif

// If you can't include the file "privateConfig.h", take a look at file "privateConfig_template.h"
#include "privateConfig.h"

/*------------------------ DEV OPTIONS ------------------------*/

// #define simulateTemperature
// #define tempPrintPeriod 500

/*------------------------ INTERFACES ------------------------*/

#define BAUDRATE 115200
#define printBufferSize 2048

#define nameHost "iogurte"

#define telegramBotToken priv_telegramBotToken
#define telegramCheckNewMessagesPeriod 1000
#define flushTelegramSerialPeriod 5000


/*------------------------ HARDWARE PINOUT ------------------------*/

#define RELAY_PIN 16
#define TEMP_PROBE_PIN 33
#define MIXING_MOTOR_PIN 3


/*------------------------ TEMPERATURE CONTROL ------------------------*/

#define tempCheckPeriod 100
#define MAX_TEMPERATURE_DIFFERENCE 2

#endif