#include "cliHandler.h"

// Preferences prefs;
cliHandler::cliHandler(HardwareSerial& serial, int baudrate)
{
    this->serial = &serial;
    this->baudrate = baudrate;

    // prefs.begin("my-app", false);
}

void cliHandler::begin()
{
    this->serial->begin(this->baudrate);
    this->input = "";

    
    cli.setOnError(errorCallback);

    
    Command wifiCmd;
    wifiCmd = cli.addCommand("wifi", wifiCallback);
    wifiCmd.addFlagArgument("add");
    wifiCmd.addFlagArgument("rem");
    wifiCmd.addFlagArgument("list");
    wifiCmd.addPositionalArgument("arg1", "");
    wifiCmd.addPositionalArgument("arg2", "");
}

void cliHandler::handle()
{
    while (this->serial->available())
    {
        char c = this->serial->read();
        this->serial->print(c);
        if(c != '\n') this->input += c;
        else
        {
            cli.parse(this->input);
            this->input = "";
        }
    }
}

void errorCallback(cmd_error* e) {
    CommandError cmdError(e); // Create wrapper object

    Serial.print("ERROR: ");
    Serial.println(cmdError.toString());

    if (cmdError.hasCommand()) {
        Serial.print("Did you mean \"");
        Serial.print(cmdError.getCommand().toString());
        Serial.println("\"?");
    }
}

void wifiCallback(cmd* c) {
    Command cmd(c);

    Argument arg1 = cmd.getArgument("arg1");
    Argument arg2 = cmd.getArgument("arg2");

    Argument add = cmd.getArgument("add");
    Argument rem = cmd.getArgument("rem");
    Argument list = cmd.getArgument("list");

    if(add.isSet())
    {
        Serial.print("Connect \"");
        Serial.print(arg1.getValue());
        Serial.print("\" \"");
        Serial.print(arg2.getValue());
        Serial.println("\"");
    }
    else if(rem.isSet())
    {
        Serial.print("Remove \"");
        Serial.print(arg1.getValue());
        Serial.println("\"");
    }
    else if(list.isSet())
    {
        Serial.println("List");
    }
    else
    {
        Serial.println("Usage:");
        Serial.println(cmd.toString());
    }
}