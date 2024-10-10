#include "telegramBot.h"

#include "globalInstances.h"

TelegramBot::TelegramBot(String telegramToken) :  // Correct constructor name
client(),
bot(telegramToken.c_str(), client),
telegramLoop(telegramCheckNewMessagesPeriod)
{
    loadActiveChat();
}

void TelegramBot::begin() // Correct method names
{
    this->client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
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
    if(telegramLoop.check())
    {
        int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

        if (numNewMessages) {
            handleNewMessages(numNewMessages);
        }
    }
}

void TelegramBot::sendText(String str)
{
    bot.sendMessage(activeChat, str, "");
}

void TelegramBot::handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    Serial.println("Received message: " + text);
    
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