#include <KTask.h>
#include <KWiFi.h>
#include <KEvent.h>
#include <KDisplay.h>
#include <KMqtt.h>

#define WIFI_SSID   "ssid"
#define WIFI_PASS   "pass"
#define MQTT_SERVER "io.adafruit.com"
#define MQTT_PORT   1883
#define MQTT_USER   "username"
#define MQTT_PASS   "aio-key"

KDisplay display;
KWiFi wifi(WIFI_SSID, WIFI_PASS);
Adafruit_WINC1500Client client;

const char MQTT_CLIENTID[] = __TIME__ MQTT_USER;
KMqtt mqtt(&client, MQTT_SERVER, MQTT_PORT, MQTT_CLIENTID, MQTT_USER, MQTT_PASS);

const char PUB_FEED[] = MQTT_USER "/feeds/display-pub";
KMqttPublish displayPub = KMqttPublish(&mqtt, PUB_FEED);
long count = 0;

void countAndDisplay() {
    display.clear();
    display.print(count++);
    display.flush();
    if (mqtt.connected()) displayPub.publish(display.get());
}

KTask counter(3000, countAndDisplay);

void updateDisplay(void *);

const char SUB_FEED[] = MQTT_USER "/feeds/display-sub";
KMqttSubscribe displaySub = KMqttSubscribe(&mqtt, SUB_FEED, updateDisplay);

void updateDisplay(KMqttSubscribe *sub, void *data) {
    char *value = (char *) sub->lastread;
    display.set(value);
}

void setup() {
    KTask::setup();
}

void loop() {
    KTask::loop();
}