#include <SPI.h>
#include <KTask.h>
#include <KWiFi.h>
#include <KHttpServer.h>
#include <KEvent.h>
#include <KMDNS.h>
#include <KMQtt.h>
#include <KWatchdog.h>

#define WIFI_SSID   "ssid"
#define WIFI_PASS   "pass"
#define MQTT_SERVER "io.adafruit.com"
#define MQTT_PORT   1883
#define MQTT_USER   "username"
#define MQTT_PASS   "aio-key"
#define MDNS_NAME   "esp"

#define LEDPIN LED_BUILTIN

KWatchdog watchdog;
KWiFi wifi(WIFI_SSID, WIFI_PASS);
KHttpServer server(80);
KMDNS mdns(MDNS_NAME);

bool ledOn = false;
void blink() {
    if (ledOn) {
        digitalWrite(LEDPIN, LOW);
        ledOn = false;
    } else {
        digitalWrite(LEDPIN, HIGH);
        ledOn = true;
    }
}

KTask blinker(500, blink);

void request(KEvent event, void *callbackData) {
    KHttpRequest *request = (KHttpRequest *) event.data;
    ArduinoHttpServer::MethodEnum method(ArduinoHttpServer::MethodInvalid);
    method = request->getMethod();
    if (method == ArduinoHttpServer::MethodGet) {
        Serial.print("GET");
    }
    else if (method == ArduinoHttpServer::MethodPost) {
        Serial.print("POST");
    }
    Serial.print(" ");
    Serial.println(request->getResource().toString());
    ArduinoHttpServer::StreamHttpReply httpReply(request->getStream(), "application/json");
    httpReply.send("{\"foo\":\"bar\"}");
};

const char MQTT_CLIENTID[] = __TIME__ MQTT_USER;
KMqtt mqtt(MQTT_SERVER, MQTT_PORT, MQTT_CLIENTID, MQTT_USER, MQTT_PASS);

const char PUB_FEED[] = MQTT_USER "/feeds/counter-pub";
KMqttPublish counterPub = KMqttPublish(&mqtt, PUB_FEED);
int32_t count = 0;

void countUp() {
    Serial.println(++count);
    if (mqtt.connected()) counterPub.publish(count);
}

KTask counter(3000, countUp);

void updateCount(void *);

const char SUB_FEED[] = MQTT_USER "/feeds/counter-sub";
KMqttSubscribe counterSub = KMqttSubscribe(&mqtt, SUB_FEED, updateCount);

void updateCount(KMqttSubscribe *sub, void *data) {
    char *value = (char *) sub->lastread;
    count = atol(value);
}

void setup() {
    Serial.begin(74880);
    pinMode(LEDPIN, OUTPUT);
    Serial.println("starting");
    KTask::setup();
    KEvent::on(KEVENT_HTTPSERVER_REQUEST, request);
}

void loop() {
    KTask::loop();
}
