#include <Arduino.h>
#include "SECRET/SECRET.hpp"
#include "WIFI/WIFI.h"
#include "MQTT/MQTT.h"

MQTT mqtt;
WIFI wifi;

#define MQTT_USERNAME "Test"
#define MQTT_PASSWORD "test"
#define MQTT_CLIENT_ID "test"
void callback(char *topic, byte *message, unsigned int length)
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
}

void setup()
{
  Serial.begin(115200);
  wifi.begin(WIFI_SSID, WIFI_PASSWORD);
  mqtt.begin(MQTT_SERVER, MQTT_PORT, callback);
  mqtt.setUser(MQTT_USERNAME, MQTT_PASSWORD, MQTT_CLIENT_ID);

  mqtt.startSubscribe("@shadow/data/updated");
  // put your setup code here, to run once:
}

void loop()
{
  mqtt.update();
  // put your main code here, to run repeatedly:
}