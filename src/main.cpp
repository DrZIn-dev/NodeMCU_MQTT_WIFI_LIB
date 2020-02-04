#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
const char *ssid = "CE-HCRL607";        // Enter your WiFi name
const char *password = "Hybrid-6Zero7"; // Enter WiFi password
const char *mqttServer = "broker.netpie.io";
const int mqttPort = 1883;
const char *mqttUser = "MniEN76eQdH8HaiquUu4vzXYGkSr2cfV";
const char *mqttPassword = "ZQcO1wAcVthla-W.IK5Sc%e+.z7bR0jL";

WiFiClient espClient;
PubSubClient client(espClient);
void callback(char *topic, byte *payload, unsigned int length)
{

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("Message:");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }

  Serial.println();
  Serial.println("-----------------------");
}

void setup()
{

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  client.publish("esp/test", "hello"); //Topic name
  client.subscribe("esp/test");
}

void loop()
{

  while (!client.connected())
  {
    Serial.println("Connecting to MQTT...");

    if (client.connect("be93c65c-eb02-46ab-9c57-fa8f9ebc160c", mqttUser, mqttPassword))
    {

      Serial.println("connected");
    }
    else
    {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  StaticJsonDocument<1024> doc;
  char json[1024];
  doc["data"]["temp"] = random(random(120324234324));
  doc["data"]["humi"] = random(random(120324234324));
  doc["data"]["pressure"] = random(random(120324234324));
  serializeJson(doc, json);
  client.publish("@shadow/data/update", json);
  client.loop();
}