#include "KMDNS.h"
#include "KEvent.h"
#include "KWiFi.h"

#ifdef ARDUINO_ARCH_ESP8266
KMDNS::KMDNS(char *n) : KTask(-1) {
#else
KMDNS::KMDNS(char *n) : KTask(10) {
#endif
    strncpy(name, n, 255);
}

void KMDNS_on_wifi_connect(KEvent event, void *callbackData) {
    KMDNS *mdns = (KMDNS *) callbackData;
#ifdef ARDUINO_ARCH_ESP8266
    MDNS.begin(mdns->name);
    MDNS.addService("http", "tcp", 80);
#else
    mdns->mdnsResponder.begin(mdns->name);
#endif
}

void KMDNS::init() {
    KEvent::on(KEVENT_WIFI_CONNECT, KMDNS_on_wifi_connect, this);
}

void KMDNS::run() {
#ifndef ARDUINO_ARCH_ESP8266
    mdnsResponder.poll();
#endif
}
