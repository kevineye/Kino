#include "KMDNS.h"
#include "KEvent.h"
#include "KWiFi.h"

KMDNS::KMDNS(char *n) : KTask(10) {
    strncpy(name, n, 255);
}

void KMDNS_on_wifi_connect(KEvent event, void *callbackData) {
    KMDNS *mdns = (KMDNS *) callbackData;
    mdns->mdnsResponder.begin(mdns->name);
}

void KMDNS::init() {
    KEvent::on(KEVENT_WIFI_CONNECT, KMDNS_on_wifi_connect, this);
}

void KMDNS::run() {
    mdnsResponder.poll();
}
