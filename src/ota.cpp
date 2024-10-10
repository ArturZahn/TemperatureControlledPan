#include "ota.h"
#include "print.h"


#if defined(ESP32_RTOS) && defined(ESP32)
void ota_handle( void * parameter ) {
    for (;;) {
        ArduinoOTA.handle();
        delay(3500);
    }
}
#endif

void setupOTA() {
    ArduinoOTA.onStart([]() {
        //NOTE: make .detach() here for all functions called by Ticker.h library - not to interrupt transfer process in any way.
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
        else // U_SPIFFS
        type = "filesystem";

        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
        myprintln("Start updating " + type);
    });
    
    ArduinoOTA.onEnd([]() {
        myprintln("\nEnd");
    });
    
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        myprint("Progress: ");
        myprint((progress / (total / 100)));
        myprintln("%");
    });
    
    ArduinoOTA.onError([](ota_error_t error) {
        myprint("Error[");
        myprint(error);
        myprintln("]: ");
        if (error == OTA_AUTH_ERROR) myprintln("\nAuth Failed");
        else if (error == OTA_BEGIN_ERROR) myprintln("\nBegin Failed");
        else if (error == OTA_CONNECT_ERROR) myprintln("\nConnect Failed");
        else if (error == OTA_RECEIVE_ERROR) myprintln("\nReceive Failed");
        else if (error == OTA_END_ERROR) myprintln("\nEnd Failed");
    });

    ArduinoOTA.begin();

    myprintln("OTA Initialized");
    // myprintln("IP address: ");
    // myprintln(WiFi.localIP());

    #if defined(ESP32_RTOS) && defined(ESP32)
    xTaskCreate(
        ota_handle,          /* Task function. */
        "OTA_HANDLE",        /* String with name of task. */
        10000,            /* Stack size in bytes. */
        NULL,             /* Parameter passed as input of the task */
        1,                /* Priority of the task. */
        NULL);            /* Task handle. */
    #endif
}