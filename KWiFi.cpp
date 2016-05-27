#include "KWiFi.h"
#include "KEvent.h"
#include <Adafruit_WINC1500.h>
#include <Arduino.h>
#include <string.h>

Adafruit_WINC1500 WiFi(WINC_CS, WINC_IRQ, WINC_RST);
char *KWiFi::ssid = NULL;
char *KWiFi::pass = NULL;

KWiFi::KWiFi(char *s, char *p) : KTask(5000) {
    ssid = s;
    pass = p;
}

#ifdef KWIFI_SERIAL_STATUS

void on_wifi_disconnect(KEvent event, void *callbackData) {
    Serial.println("WiFi disconnected.");
};

void on_wifi_connect(KEvent event, void *callbackData) {
    Serial.println("WiFi connected.");
};

void on_wifi_failed(KEvent event, void *callbackData) {
    Serial.println("WiFi connect failed.");
};

void on_wifi_connecting(KEvent event, void *callbackData) {
    Serial.println("WiFi attempting to connect...");
};
#endif

void KWiFi::init() {
#ifdef WINC_EN
    pinMode(WINC_EN, OUTPUT);
    digitalWrite(WINC_EN, HIGH);
#endif

#ifdef KWIFI_SERIAL_STATUS
    KEvent::on(KEVENT_WIFI_CONNECT, on_wifi_connect, this);
    KEvent::on(KEVENT_WIFI_CONNECTING, on_wifi_connecting, this);
    KEvent::on(KEVENT_WIFI_CONNECT_FAILED, on_wifi_failed, this);
    KEvent::on(KEVENT_WIFI_DISCONNECT, on_wifi_disconnect, this);
#endif
}

void KWiFi::run() {
//    Serial.print("connected=");
//    Serial.print(connected);
//    Serial.print(" connecting=");
//    Serial.print(connecting);
//    Serial.print(" status=");
//    Serial.println(WiFi.status());

    if (WiFi.status() != WL_NO_SHIELD) {
        // attempt to connect to Wifi network:
        if (connected && WiFi.status() != WL_CONNECTED) {
            KEvent::emit(KEVENT_WIFI_DISCONNECT, NULL);
        }
        if (connecting && WiFi.status() == WL_CONNECTED) {
            KEvent::emit(KEVENT_WIFI_CONNECT, NULL);
        }
        if (connecting && WiFi.status() == WL_CONNECT_FAILED) {
            connecting = false;
            KEvent::emit(KEVENT_WIFI_CONNECT_FAILED, NULL);
        }
        connected = WiFi.status() == WL_CONNECTED;
        if (!connecting && !connected) {
            connecting = true;
            connected = false;
            KEvent::emit(KEVENT_WIFI_CONNECTING, NULL);
            WiFi.begin(ssid, pass);
        }
    }
}
