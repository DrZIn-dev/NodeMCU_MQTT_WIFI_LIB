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
    WIFI(boolean isShow);
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
}

#endif