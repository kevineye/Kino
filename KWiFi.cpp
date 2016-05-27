#include "KWiFi.h"
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

void KWiFi::init() {
#ifdef WINC_EN
    pinMode(WINC_EN, OUTPUT);
    digitalWrite(WINC_EN, HIGH);
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
            Serial.println("WiFi disconnected.");
        }
        if (connecting && WiFi.status() == WL_CONNECTED) {
            Serial.println("WiFi connected.");
        }
        if (connecting && WiFi.status() == WL_CONNECT_FAILED) {
            connecting = false;
            Serial.println("WiFi connect failed.");
        }
        connected = WiFi.status() == WL_CONNECTED;
        if (!connecting && !connected) {
            Serial.println("WiFi attempting to connect...");
            connecting = true;
            connected = false;
            WiFi.begin(ssid, pass);
        }
    }
}
