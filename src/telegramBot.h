#ifndef TELEGRAMBOT_H
#define TELEGRAMBOT_H

#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <Preferences.h>

#include "config.h"
#include "timedLoop.h"

class TelegramBot
{
private:
    Preferences p;
    WiFiClientSecure client;
    UniversalTelegramBot bot;
    timedLoop telegramLoop;

    String activeChat;

    void handleNewMessages(int numNewMessages);
    void loadActiveChat();
    void setActiveChat(String _activeChat);
public:
    TelegramBot(String telegramToken);
    void begin();
    void handle();
    void sendText(String str);
};



void telegramBot_begin();
void telegramBot_handle();


#endif