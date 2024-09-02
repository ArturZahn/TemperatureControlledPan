#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <Arduino.h>
#include <WiFi.h>
#include <vector>
#include <Preferences.h>

class wifiManager
{
private:
    Preferences p;
    void _connect(String ssid, String passwd);
    void _autoConnect();
    void handleWifiEvent(WiFiEvent_t event, WiFiEventInfo_t info);
    void _chooseNetworkFromScanAndConnect();

    bool autoConnection;
    bool waitingScanningToAutoConnect;
    bool waitingForConnection;
public:
    std::vector<String> wifiList;
    std::vector<String> passwdList;
    wifiManager(int n);
    void begin(bool autoConnection = false);

    void enableAutoConnection();
    void disableAutoConnection();

    void handle();

    // void connect();
    // void connect(int networkNumber);
    // void connect(String ssid);
    // void connect(String ssid, String passwd);

    void addNetworkToList(String ssid, String passwd);
    void removeNetwork(String ssid);
    void removeNetwork(int id);

    void loadList();
    void saveList();

    void listSavedNetworks();
    int getNumberOfSavedNetworks();
    String getSavedNetwork(int networkNumber);
};


#endif