#include "KMqtt.h"
#include "KEvent.h"
#include "KWiFi.h"

Client *KMqtt_make_client() {
#ifdef ARDUINO_ARCH_ESP8266
    WiFiClient *client = new WiFiClient;
#else
    Adafruit_WINC1500Client *client = new Adafruit_WINC1500Client;
#endif
    return client;
}

KMqtt::KMqtt(Client *client, const char *server, uint16_t port, const char *cid, const char *user, const char *pass)
        : KTask(10), Adafruit_MQTT_Client(client, server, port, cid, user, pass) {
    wifiUp = false;
}

KMqtt::KMqtt(const char *server, uint16_t port, const char *cid, const char *user, const char *pass)
        : KTask(10), Adafruit_MQTT_Client(KMqtt_make_client(), server, port, cid, user, pass) {
    wifiUp = false;
}

void KMqtt_on_wifi_connect(KEvent event, void *callbackData) {
    KMqtt *mqtt = (KMqtt *) callbackData;
    mqtt->wifiUp = true;
    mqtt->kConnect();
}

void KMqtt_on_wifi_disconnect(KEvent event, void *callbackData) {
    KMqtt *mqtt = (KMqtt *) callbackData;
    mqtt->disconnect();
    mqtt->wifiUp = false;
}

void KMqtt::init() {
    KEvent::on(KEVENT_WIFI_CONNECT, KMqtt_on_wifi_connect, this);
    KEvent::on(KEVENT_WIFI_DISCONNECT, KMqtt_on_wifi_disconnect, this);
}

void KMqtt_call_cb(KMqttSubscribe *sub);

void KMqtt::run() {
    Adafruit_MQTT_Subscribe *subscription;
    while ((subscription = readSubscription(10))) {
        KMqttSubscribe *sub = (KMqttSubscribe *) subscription;
        KMqtt_call_cb(sub);
    }
    if (!connected() && wifiUp) {
        disconnect();
        Serial.println("MQTT disconnected. Waiting 5 seconds and retrying MQTT connection.");
        delay(5000);
        kConnect();
    }
}

void KMqtt::kConnect() {
    Serial.print("Connecting to MQTT... ");
    int8_t ret = connect();
    if (ret == 0) {
        Serial.println("connected.");
    } else {
        Serial.println(ret);
        Serial.println(connectErrorString(ret));
    }

}

KMqttPublish::KMqttPublish(KMqtt *mqttserver, const __FlashStringHelper *feed, uint8_t q) : Adafruit_MQTT_Publish(
        mqttserver, feed, q) { }

KMqttPublish::KMqttPublish(KMqtt *mqttserver, const char *feed, uint8_t q) : Adafruit_MQTT_Publish(mqttserver, feed,
                                                                                                   q) { }

KMqttSubscribe *KMqtt_callbackIndex[MAXSUBSCRIPTIONS];

void (*KMqtt_callbacks[MAXSUBSCRIPTIONS])(KMqttSubscribe *, void *);

void *KMqtt_callbackDatas[MAXSUBSCRIPTIONS];
int KMqtt_numCallbacks = 0;

void KMqtt_install_cb(KMqttSubscribe *sub, void (*cb)(KMqttSubscribe *, void *), void *data) {
    KMqtt_callbackIndex[KMqtt_numCallbacks] = sub;
    KMqtt_callbacks[KMqtt_numCallbacks] = cb;
    KMqtt_callbackDatas[KMqtt_numCallbacks] = data;
    KMqtt_numCallbacks++;
}

void KMqtt_call_cb(KMqttSubscribe *sub) {
    for (int i = 0; i < KMqtt_numCallbacks; i++) {
        if (KMqtt_callbackIndex[i] == sub) {
            (KMqtt_callbacks[i])(sub, KMqtt_callbackDatas[i]);
            return;
        }
    }
}

KMqttSubscribe::KMqttSubscribe(KMqtt *mqttserver, const __FlashStringHelper *feed, void (*cb)(KMqttSubscribe *, void *),
                               void *data, uint8_t q) : Adafruit_MQTT_Subscribe(mqttserver, feed, q) {
    KMqtt_install_cb(this, cb, data);
    mqttserver->subscribe(this);
}

KMqttSubscribe::KMqttSubscribe(KMqtt *mqttserver, const char *feed, void (*cb)(KMqttSubscribe *, void *), void *data,
                               uint8_t q) : Adafruit_MQTT_Subscribe(mqttserver, feed, q) {
    KMqtt_install_cb(this, cb, data);
    mqttserver->subscribe(this);
}

