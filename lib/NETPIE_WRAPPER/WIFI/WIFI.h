#ifndef WIFI_WRAPPER
#define WIFI_WRAPPER
#include <Arduino.h>
#include "MACROS/MACROS.h"
#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif
class WIFI : private MACROS
{
private:
    char *SSID;
    char *PASSWORD;
    char *IP;
    char *STATUS;

public:
    WIFI(boolean isShow = true);
    ~WIFI();

    void begin(const char *SSID, const char *PASSWORD);
    char *getSSID();
    char *getIP();
    boolean getStatus();
};

WIFI::WIFI(boolean isShow) : MACROS(isShow)
{
}

WIFI::~WIFI()
{
}

void WIFI::begin(const char *SSID, const char *PASSWORD)
{
    this->SSID = (char *)SSID;

    WiFi.begin(this->SSID, PASSWORD);
    Sprintln("Connect to : " + String(this->SSID));
    Sprint("Start Connection => [ ");
    int startTime = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        Sprint("=");
        delay(100);
        if (millis() - startTime > Sec2MS(10))
        {
            ESP.restart();
        }
    }
    Sprintln(" ] 100% ");
    Sprintln("WiFi Connected");
    Sprint("Local IP : ");

    this->IP = (char *)WiFi.localIP().toString().c_str();
    Sprintln(this->IP);
}

char *WIFI::getSSID()
{
    return this->SSID;
}
char *WIFI::getIP()
{
    return this->IP;
}
boolean WIFI::getStatus()
{
    return (boolean)WiFi.isConnected();
}
#endif