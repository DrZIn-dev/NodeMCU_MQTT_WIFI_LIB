#include <Arduino.h>
#include "WIFI/WIFI.h"
#include "MACROS/MACROS.h"
#define WIFI_SSID "MakeEdu"
#define WIFI_PASS "Hybrid-6Zero7"
#define CLIENT_ID ""
#define CLIENT_USERNAME ""
#define CLIENT_PASSWORD ""
#define MQTT_SERVER ""
#define MQTT_PORT 1883

#define PUB_MSG_DATA ""
#define PUB_SHADOW_DATA ""

MACROS macros;
void setup()
{
  Serial.begin(115200);
  macros.Sprintln("Hello");
  // put your setup code here, to run once:
}

void loop()
{
  // put your main code here, to run repeatedly:
}