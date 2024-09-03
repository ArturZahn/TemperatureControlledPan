#include <WiFi.h>

String getEventName(WiFiEvent_t event)
{
    switch (event)
    {
        case ARDUINO_EVENT_WIFI_READY: return "ARDUINO_EVENT_WIFI_READY";
        case ARDUINO_EVENT_WIFI_SCAN_DONE: return "ARDUINO_EVENT_WIFI_SCAN_DONE";
        case ARDUINO_EVENT_WIFI_STA_START: return "ARDUINO_EVENT_WIFI_STA_START";
        case ARDUINO_EVENT_WIFI_STA_STOP: return "ARDUINO_EVENT_WIFI_STA_STOP";
        case ARDUINO_EVENT_WIFI_STA_CONNECTED: return "ARDUINO_EVENT_WIFI_STA_CONNECTED";
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED: return "ARDUINO_EVENT_WIFI_STA_DISCONNECTED";
        case ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE: return "ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE";
        case ARDUINO_EVENT_WIFI_STA_GOT_IP: return "ARDUINO_EVENT_WIFI_STA_GOT_IP";
        case ARDUINO_EVENT_WIFI_STA_GOT_IP6: return "ARDUINO_EVENT_WIFI_STA_GOT_IP6";
        case ARDUINO_EVENT_WIFI_STA_LOST_IP: return "ARDUINO_EVENT_WIFI_STA_LOST_IP";
        case ARDUINO_EVENT_WIFI_AP_START: return "ARDUINO_EVENT_WIFI_AP_START";
        case ARDUINO_EVENT_WIFI_AP_STOP: return "ARDUINO_EVENT_WIFI_AP_STOP";
        case ARDUINO_EVENT_WIFI_AP_STACONNECTED: return "ARDUINO_EVENT_WIFI_AP_STACONNECTED";
        case ARDUINO_EVENT_WIFI_AP_STADISCONNECTED: return "ARDUINO_EVENT_WIFI_AP_STADISCONNECTED";
        case ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED: return "ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED";
        case ARDUINO_EVENT_WIFI_AP_PROBEREQRECVED: return "ARDUINO_EVENT_WIFI_AP_PROBEREQRECVED";
        case ARDUINO_EVENT_WIFI_AP_GOT_IP6: return "ARDUINO_EVENT_WIFI_AP_GOT_IP6";
        case ARDUINO_EVENT_WIFI_FTM_REPORT: return "ARDUINO_EVENT_WIFI_FTM_REPORT";
        case ARDUINO_EVENT_ETH_START: return "ARDUINO_EVENT_ETH_START";
        case ARDUINO_EVENT_ETH_STOP: return "ARDUINO_EVENT_ETH_STOP";
        case ARDUINO_EVENT_ETH_CONNECTED: return "ARDUINO_EVENT_ETH_CONNECTED";
        case ARDUINO_EVENT_ETH_DISCONNECTED: return "ARDUINO_EVENT_ETH_DISCONNECTED";
        case ARDUINO_EVENT_ETH_GOT_IP: return "ARDUINO_EVENT_ETH_GOT_IP";
        case ARDUINO_EVENT_ETH_GOT_IP6: return "ARDUINO_EVENT_ETH_GOT_IP6";
        case ARDUINO_EVENT_WPS_ER_SUCCESS: return "ARDUINO_EVENT_WPS_ER_SUCCESS";
        case ARDUINO_EVENT_WPS_ER_FAILED: return "ARDUINO_EVENT_WPS_ER_FAILED";
        case ARDUINO_EVENT_WPS_ER_TIMEOUT: return "ARDUINO_EVENT_WPS_ER_TIMEOUT";
        case ARDUINO_EVENT_WPS_ER_PIN: return "ARDUINO_EVENT_WPS_ER_PIN";
        case ARDUINO_EVENT_WPS_ER_PBC_OVERLAP: return "ARDUINO_EVENT_WPS_ER_PBC_OVERLAP";
        case ARDUINO_EVENT_SC_SCAN_DONE: return "ARDUINO_EVENT_SC_SCAN_DONE";
        case ARDUINO_EVENT_SC_FOUND_CHANNEL: return "ARDUINO_EVENT_SC_FOUND_CHANNEL";
        case ARDUINO_EVENT_SC_GOT_SSID_PSWD: return "ARDUINO_EVENT_SC_GOT_SSID_PSWD";
        case ARDUINO_EVENT_SC_SEND_ACK_DONE: return "ARDUINO_EVENT_SC_SEND_ACK_DONE";
        case ARDUINO_EVENT_PROV_INIT: return "ARDUINO_EVENT_PROV_INIT";
        case ARDUINO_EVENT_PROV_DEINIT: return "ARDUINO_EVENT_PROV_DEINIT";
        case ARDUINO_EVENT_PROV_START: return "ARDUINO_EVENT_PROV_START";
        case ARDUINO_EVENT_PROV_END: return "ARDUINO_EVENT_PROV_END";
        case ARDUINO_EVENT_PROV_CRED_RECV: return "ARDUINO_EVENT_PROV_CRED_RECV";
        case ARDUINO_EVENT_PROV_CRED_FAIL: return "ARDUINO_EVENT_PROV_CRED_FAIL";
        case ARDUINO_EVENT_PROV_CRED_SUCCESS: return "ARDUINO_EVENT_PROV_CRED_SUCCESS";
        case ARDUINO_EVENT_MAX: return "ARDUINO_EVENT_MAX";
    }
    return "UNKNOWN";
}