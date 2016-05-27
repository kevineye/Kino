#include "KWiFi.h"
#include <Arduino.h>
#include <Scheduler.h>
#include <string.h>

Adafruit_WINC1500 WiFi(WINC_CS, WINC_IRQ, WINC_RST);
char *KWiFi::ssid = NULL;
char *KWiFi::pass = NULL;

KWiFi::KWiFi(char *s, char *p) {
    ssid = s;
    pass = p;
}

void KWiFi::setup() {
#ifdef WINC_EN
    pinMode(WINC_EN, OUTPUT);
    digitalWrite(WINC_EN, HIGH);
#endif
    Scheduler.start(NULL, KWiFi::loop);
}

void KWiFi::loop() {
    if (WiFi.status() != WL_NO_SHIELD) {
        Serial.println("Connecting");
        // attempt to connect to Wifi network:
        while (WiFi.status() != WL_CONNECTED) {
            WiFi.begin(ssid, pass);

            // wait 10 seconds for connection:
            uint8_t timeout = 10;
            while (timeout && (WiFi.status() != WL_CONNECTED)) {
                timeout--;
                delay(1000);
            }
        }

        Serial.println("Connected to wifi");
    }
    Serial.println("Before delay");
    delay(1000);
    Serial.println("After delay");
}
