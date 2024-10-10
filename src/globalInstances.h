#ifndef GLOBALINSTANCES_H
#define GLOBALINSTANCES_H

#include <Preferences.h>


#include "telegramBot.h"
#include "config.h"
#include "temperatureControl.h"
#include "actuatorsControl.h"
#include "cliHandler.h"
#include "wifiManager.h"

extern TelegramBot telegBot;
extern temperatureControl tempCtrl;
extern actuatorsControl actuatorsCtrl;
extern cliHandler espcli;
extern wifiManager wifiMan;

#endif