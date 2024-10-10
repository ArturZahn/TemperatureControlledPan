#include "globalInstances.h"

temperatureControl tempCtrl(TEMP_PROBE_PIN, RELAY_PIN, false);
actuatorsControl actuatorsCtrl(MIXING_MOTOR_PIN);
cliHandler espcli(Serial, BAUDRATE);
wifiManager wifiMan(1);
TelegramBot telegBot(telegramBotToken); 
