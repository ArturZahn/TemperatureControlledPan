#include "telegramBot.h"

#include "globalInstances.h"

TelegramBot::TelegramBot(String telegramToken) :  // Correct constructor name
client(),
bot(telegramToken.c_str(), client),
newMessagesLoop(telegramCheckNewMessagesPeriod),
serialTelegramLoop(flushTelegramSerialPeriod)
{
}

void TelegramBot::begin() // Correct method names
{
    this->client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
    loadActiveChat();
}

void TelegramBot::loadActiveChat()
{
    p.begin("telegramBot");
    activeChat = p.getString("activeChat", "");
}

void TelegramBot::setActiveChat(String _activeChat)
{
    activeChat = _activeChat;
    p.putString("activeChat", _activeChat);
}

void TelegramBot::handle() // Correct method names
{
    if(newMessagesLoop.check())
    {
        int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

        if (numNewMessages) {
            handleNewMessages(numNewMessages);
        }
    }

    if(serialTelegramLoop.check())
    {
        telegBot.telegramSerialSendBuffer();
    }
}

void TelegramBot::telegramSerialSendBuffer()
{
    if(activeChat != "" && WiFi.status() == WL_CONNECTED && myprintObj.printBuffer.getLength() > 0)
    {
        bot.sendMessage(activeChat, myprintObj.printBuffer.readBuffer(), "");
    }
}

void TelegramBot::handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    myprintln("Received message: " + text);
    
    // Check message content and respond
    if (text == "/start")
    {
        bot.sendMessage(chat_id, "Agora esse chat será usado para controlar a iogurteira", "");
        setActiveChat(chat_id);
    }
    else if(activeChat == chat_id)
    {
        espcli.parseCliCommand(text);
    }
    else
    {
        bot.sendMessage(chat_id, "Comando não existe", "");
    }
  }
}