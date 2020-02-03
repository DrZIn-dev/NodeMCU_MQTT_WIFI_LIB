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

    String topicLst[100];

    WiFiClient client;
    PubSubClient mqtt;
    void addTopic(const char *topic);
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
}

MQTT::~MQTT()
{
}

void MQTT::begin(const char *host, uint32 port, MQTT_CALLBACK_SIGNATURE)
{
    this->server = (char *)host;
    this->port = port;
    this->mqtt.setServer(this->server, this->port);
    this->mqtt.setCallback(callback);
}

void MQTT::setUser(const char *username, const char *password, const char *clientID)
{
}
void MQTT::startSubscribe(const char *topic)
{
}
void MQTT::publish(const char *topic, const char *payload)
{
}

void MQTT::update()
{
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

#endif // MQ