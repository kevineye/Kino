#include "KTask.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#ifndef KMQTT_H
#define KMQTT_H

class KMqtt : protected KTask, public Adafruit_MQTT_Client {
public:
    KMqtt(Client *client, const char *server, uint16_t port, const char *cid, const char *user, const char *pass);

    void kConnect();

    bool wifiUp;

protected:
    virtual void init() override;

    virtual void run() override;

};

class KMqttPublish : public Adafruit_MQTT_Publish {
public:
    KMqttPublish(KMqtt *mqttserver, const char *feed, uint8_t qos = 0);

    KMqttPublish(KMqtt *mqttserver, const __FlashStringHelper *feed, uint8_t qos = 0);
};

class KMqttSubscribe : public Adafruit_MQTT_Subscribe {
public:
    KMqttSubscribe(KMqtt *mqttserver, const char *feed, void (*callback)(KMqttSubscribe *, void *) = NULL,
                   void *data = NULL, uint8_t qos = 0);

    KMqttSubscribe(KMqtt *mqttserver, const __FlashStringHelper *feed,
                   void (*callback)(KMqttSubscribe *, void *) = NULL, void *data = NULL, uint8_t qos = 0);
};

#endif
