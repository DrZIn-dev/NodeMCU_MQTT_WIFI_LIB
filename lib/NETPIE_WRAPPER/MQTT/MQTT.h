#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include <WiFiClient.h>

#include "MACROS/MACROS.h"
#include "PubSubClient/PubSubClient.h"
#include "PubSubClient/PubSubClient.cpp"

/*
    private 
        username
        client id 
        port 
        server 
    
    public 
        begin(server,port,callback)
        setuser(clientID,username,password)
        update()

        startSubscribe
        publish 

        getAllSubscribe 
        getAllPublish 

        addtopic 
        printtopic 
        
*/

class MQTT : private MACROS
{
private:
    /* data */
    char *username;
    char *password;
    char *clientID;
    char *server;
    uint32_t port;
    boolean haveUser;
    String topicLst[100];

    WiFiClient client;
    PubSubClient mqtt;
    void add2List(const char *topic);
    void reConnect();
    void subscribeFromList();

public:
    MQTT(boolean isShow = true);
    ~MQTT();

    void begin(const char *host, uint32_t port, MQTT_CALLBACK_SIGNATURE);
    void setUser(const char *username, const char *password, const char *clientID);
    void startSubscribe(const char *topic);
    void publish(const char *topic, const char *payload);
    void update();

    char *getUser();
    char *getClientID();
    uint32_t getPort();
    char *getServer();
};

MQTT::MQTT(boolean isShow) : MACROS(isShow)
{
    this->mqtt = PubSubClient(this->client);
    this->haveUser = false;

    this->username = "invalid";
    this->clientID = "invalid";
}

MQTT::~MQTT()
{
}

//---------------------------------------------------------------- public method --------------------------------

void MQTT::begin(const char *host, uint32 port, MQTT_CALLBACK_SIGNATURE)
{
    this->server = (char *)host;
    this->port = port;

    this->mqtt.setServer(this->server, this->port);
    this->mqtt.setCallback(callback);
}

void MQTT::setUser(const char *username, const char *password, const char *clientID)
{
    this->username = (char *)username;
    this->password = (char *)password;
    this->clientID = (char *)clientID;

    this->haveUser = true;
}
void MQTT::startSubscribe(const char *topic)
{
    this->add2List(topic);
}

void MQTT::publish(const char *topic, const char *payload)
{
    if (!this->mqtt.connected())
    {
        this->reConnect();
    }
    this->mqtt.publish(topic, payload);
}

void MQTT::update()
{
    if (!this->mqtt.connected())
    {
        this->reConnect();
    }
    this->mqtt.loop();
}

char *MQTT::getUser()
{
    return this->username;
}
char *MQTT::getClientID()
{
    return this->clientID;
}
uint32_t MQTT::getPort()
{
    return this->port;
}
char *MQTT::getServer()
{
    return this->server;
}

//---------------------------------------------------------------- public method --------------------------------

//---------------------------------------------------------------- private method --------------------------------

void MQTT::add2List(const char *topic)
{
    int Index = 0;
    boolean isAdded = false;
    while (!isAdded)
    {
        if (!this->topicLst[Index].equals(topic))
        {
            if (this->topicLst[Index].length() == 0)
            {
                this->topicLst[Index] = topic;
                isAdded = !isAdded;
                Sprintln("Topic Added : " + String(this->topicLst[Index]));
            }
            else
            {
                Index += 1;
            }
        }
        else
        {
            break;
        }
    }
}
void MQTT::reConnect()
{

    while (!this->mqtt.connected())
    {
        Sprintln("Attempting MQTT connection...");
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);

        if (!this->haveUser ? this->mqtt.connect(clientId.c_str()) : this->mqtt.connect(this->clientID, this->username, this->password))
        {
            Sprintln("Connected");
            this->subscribeFromList();
            this->mqtt.publish("M5/Start", "Hello world");
            this->mqtt.subscribe("Node/Start");
        }
        else
        {
            Sprint("failed, rc=");
            Sprint(this->mqtt.state());
            Sprintln("");
            delay(100);
        }
    }
}
void MQTT::subscribeFromList()
{
    int Index = 0;
    while (this->topicLst[Index].length() != 0)
    {
        char buffer[512];
        this->topicLst[Index].toCharArray(buffer, topicLst[Index].length() + 1);
        this->mqtt.subscribe(buffer);
        Sprintln("Start Subscribe =>" + String(buffer));
        Index++;
    }
}

//---------------------------------------------------------------- private method --------------------------------

#endif // MQ