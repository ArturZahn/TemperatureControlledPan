#include "wifiManager.h"
#include "getEventType.h"

wifiManager::wifiManager(int n, unsigned long autoConnectionCheckPeriod):
wifiAutoConnectionLoop(autoConnectionCheckPeriod)
{

}

void wifiManager::begin(bool enableAutoConnection)
{
    myprintln("begining");
    this->p.begin("wifi-config", false);

    this->loadList();

    WiFi.mode(WIFI_STA);

    WiFi.onEvent([this](arduino_event_id_t event, arduino_event_info_t info) { 
        this->handleWifiEvent(event, info); 
    });

    this->waitingScanningToAutoConnect = false;
    this->waitingForConnection = false;

    if(enableAutoConnection) this->enableAutoConnection();
    else this->disableAutoConnection();
}

void wifiManager::handle()
{
    if(this->autoConnection && this->wifiAutoConnectionLoop.check())
    {
        if(!waitingScanningToAutoConnect && !waitingForConnection)
        {
            if(WiFi.status() != WL_CONNECTED)
            {
                this->_autoConnect();
            }
        }
    }
}

void wifiManager::handleWifiEvent(WiFiEvent_t event, WiFiEventInfo_t info)
{
    myprintln("event trigered: ");
    myprintln(getEventName(event));

    switch (event)
    {
    case SYSTEM_EVENT_SCAN_DONE:
        if(this->waitingScanningToAutoConnect)
        {
            this->_chooseNetworkFromScanAndConnect();
            this->waitingScanningToAutoConnect = false;
        }
        WiFi.scanDelete();
        break;    
    case SYSTEM_EVENT_STA_CONNECTED:
        if(this->waitingForConnection)
        {
            myprintln("Connected successfully");
            this->waitingForConnection = false;
        }

        break;    
    case SYSTEM_EVENT_STA_DISCONNECTED:
        if(this->waitingForConnection)
        {
            myprintln("Could not connect to selected network");
            this->waitingForConnection = false;
        }
        break;
    default:
        break;
    }
}

void wifiManager::enableAutoConnection()
{
    myprintln("enabling auto connect");
    this->autoConnection = true;
    this->_autoConnect();
}
void wifiManager::disableAutoConnection()
{
    myprintln("disabling auto connect");
    this->autoConnection = false;
}

void wifiManager::_autoConnect()
{
    myprintln("beginning of auto connect");
    this->waitingScanningToAutoConnect = true;
    
    myprintln("getting networks...");
    WiFi.scanNetworks(true);
}

void wifiManager::_connect(String ssid, String passwd)
{
    myprint("connecting to ");
    myprintln(ssid);
    
    this->waitingForConnection = true;
    WiFi.begin(ssid, passwd);

    this->startMDNS();
}

void wifiManager::startMDNS()
{
    if (!MDNS.begin(nameHost)) {
        myprintln("Erro ao configurar o mDNS");
    }
}

void wifiManager::_chooseNetworkFromScanAndConnect()
{
    myprintln("choosing network to connect");
    int n = WiFi.scanComplete();

    if(n == -2)
    {
        myprintln("There isn't a network scan yet");
        return;
    }

    int bestWifiId = -1;
    int bestWifiIndexInList = -1;

    for (int i = 0; i < n; i++) {
        auto it = std::find(this->wifiList.begin(), this->wifiList.end(), WiFi.SSID(i));

        if(it != this->wifiList.end())
        {
            myprint(">");
            if(bestWifiId == -1 || WiFi.RSSI(i) > WiFi.RSSI(bestWifiId))
            {
                bestWifiId = i;
                bestWifiIndexInList = std::distance(wifiList.begin(), it);
            }
        }
        myprintln(WiFi.SSID(i));
    }

    if(bestWifiIndexInList != -1)
    {
        myprint("chosen network: ");
        myprintln(this->wifiList[bestWifiIndexInList]);

        this->_connect(this->wifiList[bestWifiIndexInList], this->passwdList[bestWifiIndexInList]);
    }
    else myprintln("network not found");
}

/*----------------------------- WIFI LIST HANDLING -----------------------------*/

void wifiManager::loadList()
{
    this->wifiList.clear();
    String listStr = this->p.getString("wifiList");
    int startIndex = 0;
    int endIndex = 0;
    while ((endIndex = listStr.indexOf('\n', startIndex)) != -1)
    {
        String token = listStr.substring(startIndex, endIndex);
        this->wifiList.push_back(token);
        startIndex = endIndex + 1;
    }
    
    this->passwdList.clear();
    listStr = this->p.getString("passwdList");
    startIndex = 0;
    endIndex = 0;
    while ((endIndex = listStr.indexOf('\n', startIndex)) != -1)
    {
        String token = listStr.substring(startIndex, endIndex);
        this->passwdList.push_back(token);
        startIndex = endIndex + 1;
    }

    if(this->wifiList.size() != this->passwdList.size())
    {
        myprintln("Error in saved wifi");
        this->wifiList.clear();
        this->passwdList.clear();
    }
}
void wifiManager::saveList()
{
    String strList = "";
    for (int i = 0; i < this->wifiList.size(); i++)
    {
        strList += this->wifiList[i]+"\n";
    }
    this->p.putString("wifiList", strList);

    strList = "";
    for (int i = 0; i < this->passwdList.size(); i++)
    {
        strList += this->passwdList[i]+"\n";
    }
    this->p.putString("passwdList", strList);
}
int wifiManager::getNumberOfSavedNetworks()
{
    return this->wifiList.size();
}
String wifiManager::getSavedNetwork(int networkIndex)
{
    return this->wifiList[networkIndex];
}
void wifiManager::listSavedNetworks()
{
    myprintln("Saved WIFIs:");
    for (int i = 0; i < this->wifiList.size(); i++)
    {
        myprint("    \"");
        myprint(this->wifiList[i]);
        myprint("\" \"");
        myprint(this->passwdList[i]);
        myprintln("\"");
    }
}
void wifiManager::addNetworkToList(String ssid, String passwd)
{
    for (int i = 0; i < this->wifiList.size(); i++)
    {
        if(this->wifiList[i] == ssid)
        {
            this->passwdList[i] = passwd;
            return;
        }
    }

    this->wifiList.push_back(ssid);
    this->passwdList.push_back(passwd);

    this->saveList();
}
bool wifiManager::removeNetwork(String ssid)
{
    auto it = std::find(this->wifiList.begin(), this->wifiList.end(), ssid);
    
    if(it == this->wifiList.end()) return false;

    int indexToRemove = std::distance(wifiList.begin(), it);

    this->wifiList.erase(it);
    this->passwdList.erase(this->passwdList.begin() + indexToRemove);
    this->saveList();

    return true;
}
bool wifiManager::removeNetwork(int id)
{
    if(id >= this->wifiList.size()) return false;
    
    this->wifiList.erase(this->wifiList.begin() + id);
    this->passwdList.erase(this->passwdList.begin() + id);
    this->saveList();

    return true;
}


/*----------------------------- OTHER PUBLIC FUNCTIONS -----------------------------*/

void wifiManager::autoConnect()
{
    this->_autoConnect();
}

void wifiManager::addAndConnect(String ssid, String passwd)
{
    this->addNetworkToList(ssid, passwd);
    this->_connect(ssid, passwd);
}

bool wifiManager::connect(String ssid)
{
    for (int i = 0; i < this->wifiList.size(); i++)
    {
        if(this->wifiList[i] == ssid)
        {
            this->_connect(ssid, this->passwdList[i]);
            return true;
        }
    }

    return false;
}

bool wifiManager::connect(int networkIndex)
{
    if(networkIndex >= this->wifiList.size()) return false;

    this->_connect(this->wifiList[networkIndex], this->passwdList[networkIndex]);
    return true;
}

void wifiManager::disconnect()
{
    WiFi.disconnect();
}

void wifiManager::listAvailableNetworks()
{
    myprint("Scanning for available networks...");
    
    // Start the scan
    int n = WiFi.scanNetworks();
    
    if (n == 0)
    {
        myprint("No networks found.");
    }
    else
    {
        myprint("Networks found:");
        
        for (int i = 0; i < n; ++i)
        {
            // Print SSID, signal strength (RSSI), and encryption type
            myprint(i + 1);
            myprint(": ");
            myprint(WiFi.SSID(i));
            myprint(" (");
            myprint(WiFi.RSSI(i));
            myprint(" dBm)");
            myprint(" Encryption: ");
            myprint(WiFi.encryptionType(i) == WIFI_AUTH_OPEN ? "Open" : "Encrypted");
            
            delay(10);
        }
    }

}