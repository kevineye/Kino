#include <SPI.h>
#include <KTask.h>
#include <KEvent.h>
#include <KWiFi.h>
#include <KHttpServer.h>
#include <KMDNS.h>
#include <KMqtt.h>
#include <KButton.h>
#include <KDisplay.h>
#include <KWatchdog.h>

#define BUTTON_A    9
#define BUTTON_B    6
#define BUTTON_C    5
#define LEDPIN      LED_BUILTIN

#define WIFI_SSID   "ssid"
#define WIFI_PASS   "pass"
#define MQTT_SERVER "io.adafruit.com"
#define MQTT_PORT   1883
#define MQTT_USER   "username"
#define MQTT_PASS   "aio-key"
#define MDNS_NAME   "feather"

KWatchdog watchdog;
KDisplay display;
KWiFi wifi(WIFI_SSID, WIFI_PASS);
Adafruit_WINC1500Client client;

KHttpServer server(80);
KMDNS mdns(MDNS_NAME);

char ledState[2] = "0";

const char MQTT_CLIENTID[] = __TIME__ MQTT_USER;
KMqtt mqtt(&client, MQTT_SERVER, MQTT_PORT, MQTT_CLIENTID, MQTT_USER, MQTT_PASS);

const char DISPLAY_FEED[] = MQTT_USER "/feeds/display";
KMqttPublish displayPub = KMqttPublish(&mqtt, DISPLAY_FEED);

void updateDisplay(KMqttSubscribe *sub, void *data) {
    char *value = (char *) sub->lastread;
    display.set(value);
}

KMqttSubscribe displaySub = KMqttSubscribe(&mqtt, DISPLAY_FEED, updateDisplay);

void updateDisplay(void *);
const char LED_FEED[] = MQTT_USER "/feeds/led";
KMqttSubscribe ledSub = KMqttSubscribe(&mqtt, LED_FEED, updateLed);
KMqttPublish ledPub = KMqttPublish(&mqtt, LED_FEED);
void updateLed(KMqttSubscribe *sub, void *data) {
    char *value = (char *) sub->lastread;
    if (strcmp(value, "1") == 0) {
        digitalWrite(LEDPIN, HIGH);
        ledState[0] = '1';
    } else {
        digitalWrite(LEDPIN, LOW);
        ledState[0] = '0';
    }
}

void connect(KEvent event, void *callbackData) {
    display.clear();
    display.print("Connected to ");
    display.println(wifi.wifi->SSID());
    display.print("http://");
    IPAddress ip = wifi.wifi->localIP();
    display.println(ip);
    display.print("http://");
    display.print(mdns.name);
    display.println(".local");
    display.flush();
};

void request(KEvent event, void *callbackData) {
    KHttpRequest *request = (KHttpRequest *) event.data;
    ArduinoHttpServer::MethodEnum method(ArduinoHttpServer::MethodInvalid);
    method = request->getMethod();
    const String path = request->getResource().toString();
    if (path == "/display") {
        if (method == ArduinoHttpServer::MethodGet) {
            ArduinoHttpServer::StreamHttpReply httpReply(request->getStream(), "text/plain");
            httpReply.send(display.get());
        } else if (method == ArduinoHttpServer::MethodPut) {
            display.set((char *) request->getBody());
            if (mqtt.connected()) displayPub.publish(display.get());
            ArduinoHttpServer::StreamHttpReply httpReply(request->getStream(), "text/plain");
            httpReply.send(display.get());
        }
    } else if (path == "/led") {
        if (method == ArduinoHttpServer::MethodGet) {
            ArduinoHttpServer::StreamHttpReply httpReply(request->getStream(), "text/plain");
            httpReply.send(ledState);
        } else if (method == ArduinoHttpServer::MethodPut) {
            if (strcmp(request->getBody(), "1") == 0) {
                digitalWrite(LEDPIN, HIGH);
                ledState[0] = '1';
            } else {
                digitalWrite(LEDPIN, LOW);
                ledState[0] = '0';
            }
            if (mqtt.connected()) ledPub.publish(ledState);
            ArduinoHttpServer::StreamHttpReply httpReply(request->getStream(), "text/plain");
            httpReply.send(ledState);
        }
    }
};

const char BUTTON_A_FEED[] = MQTT_USER "/feeds/button-a";
KMqttPublish buttonAPub = KMqttPublish(&mqtt, BUTTON_A_FEED);
void press_a(KButton *button) {
    if (mqtt.connected()) buttonAPub.publish((uint32_t) 1);
}
void release_a(KButton *button) {
    if (mqtt.connected()) buttonAPub.publish((uint32_t) 0);
}
KButton buttonA(BUTTON_A, press_a, release_a);

const char BUTTON_B_FEED[] = MQTT_USER "/feeds/button-b";
KMqttPublish buttonBPub = KMqttPublish(&mqtt, BUTTON_B_FEED);
void press_b(KButton *button) {
    if (mqtt.connected()) buttonBPub.publish((uint32_t) 1);
}
void release_b(KButton *button) {
    if (mqtt.connected()) buttonBPub.publish((uint32_t) 0);
}
KButton buttonB(BUTTON_B, press_b, release_b);

const char BUTTON_C_FEED[] = MQTT_USER "/feeds/button-c";
KMqttPublish buttonCPub = KMqttPublish(&mqtt, BUTTON_C_FEED);
void press_c(KButton *button) {
    if (mqtt.connected()) buttonCPub.publish((uint32_t) 1);
}
void release_c(KButton *button) {
    if (mqtt.connected()) buttonCPub.publish((uint32_t) 0);
}
KButton buttonC(BUTTON_C, press_c, release_c);


void setup() {
    pinMode(LEDPIN, OUTPUT);
    KTask::setup();
    KEvent::on(KEVENT_WIFI_CONNECT, connect);
    KEvent::on(KEVENT_HTTPSERVER_REQUEST, request);
}

void loop() {
    KTask::loop();
}

char * timeToString(unsigned long t)
{
    static char str[12];
    long h = t / 3600;
    t = t % 3600;
    int m = t / 60;
    int s = t % 60;
    sprintf(str, "%04ld:%02d:%02d", h, m, s);
    return str;
}

void displayTime() {
    display.display.fillRect(11*6, 3*8, 10*6, 1*8, 0);
    display.display.setCursor(11*6, 3*8);
    display.display.print(timeToString(millis()/1000));
    display.display.display();
}
KTask displayTimer(1000, displayTime);

const char RUNTIME_FEED[] = MQTT_USER "/feeds/runtime";
KMqttPublish runtimePub = KMqttPublish(&mqtt, RUNTIME_FEED);

void publishTime() {
    if (mqtt.connected()) runtimePub.publish(timeToString(millis()/1000));
}
KTask publishTimer(15000, publishTime);

