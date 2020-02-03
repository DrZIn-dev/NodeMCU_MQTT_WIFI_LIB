#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include "PubSubClient/PubSubClient.h"
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
class MQTT
{
private:
    /* data */
public:
    MQTT(/* args */);
    ~MQTT();
};

MQTT::MQTT(/* args */)
{
}

MQTT::~MQTT()
{
}

#endif // MQ