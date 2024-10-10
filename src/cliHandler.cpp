#include "cliHandler.h"

#include "globalInstances.h"

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
    wifiCmd.addFlagArgument("con");
    wifiCmd.addFlagArgument("dis");
    wifiCmd.addFlagArgument("add");
    wifiCmd.addFlagArgument("rem");
    wifiCmd.addFlagArgument("list");
    wifiCmd.addFlagArgument("status");
    wifiCmd.addPositionalArgument("arg1", "");
    wifiCmd.addPositionalArgument("arg2", "");

    Command restartCmd;
    restartCmd = cli.addCommand("restart", restartCallback);
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

    Argument con = cmd.getArgument("con");
    Argument dis = cmd.getArgument("dis");
    Argument add = cmd.getArgument("add");
    Argument rem = cmd.getArgument("rem");
    Argument list = cmd.getArgument("list");
    Argument status = cmd.getArgument("status");

    if(con.isSet())
    {
        if(arg2.getValue() != "")
        {
            wifiMan.addAndConnect(arg1.getValue(), arg2.getValue());
        }
        else
        {
            if(arg1.getValue() != "")
            {
                if(!wifiMan.connect(arg1.getValue()))
                    Serial.println("This wifi doesnt exist");
            }
            else wifiMan.autoConnect();
        }
    }
    else if(dis.isSet())
    {
        wifiMan.disconnect();
    }
    else if(rem.isSet())
    {
        if(wifiMan.removeNetwork(arg1.getValue())) 
            Serial.println("Removed");
        else Serial.println("This network isnt known");
    }
    else if(add.isSet())
    {
        if(arg1.getValue() != "")
        {
            wifiMan.addNetworkToList(arg1.getValue(), arg2.getValue());
        }
    }
    else if(list.isSet())
    {
        wifiMan.listSavedNetworks();
    }
    else if(status.isSet())
    {
        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("Connected to network: " + WiFi.SSID());

            Serial.print("IP Address: ");
            Serial.println(WiFi.localIP());

            Serial.print("Signal strength (RSSI): ");
            Serial.println(WiFi.RSSI());
        } else {
            Serial.println("WiFi is not connected");
        }
    }
    else
    {
        Serial.println("Usage:");
        Serial.println(cmd.toString());
    }
}

void restartCallback(cmd* c)
{
    ESP.restart();
}