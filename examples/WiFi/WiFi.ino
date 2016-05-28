#include <KTask.h>
#include <KWiFi.h>
#include <KEvent.h>
#include <KDisplay.h>

KDisplay display;

KWiFi wifi("ssid", "pass");

void disconnect(KEvent event, void *callbackData) {
    display.set("Disconnected");
};

void connect(KEvent event, void *callbackData) {
    display.set("Connected!");
};

void failed(KEvent event, void *callbackData) {
    display.set("Connection failed");
};

void connecting(KEvent event, void *callbackData) {
    display.set("Attempting to connect");
};

void setup() {
    KTask::setup();
    KEvent::on(KEVENT_WIFI_CONNECT, connect);
    KEvent::on(KEVENT_WIFI_CONNECTING, connecting);
    KEvent::on(KEVENT_WIFI_CONNECT_FAILED, failed);
    KEvent::on(KEVENT_WIFI_DISCONNECT, disconnect);
}

void loop() {
    KTask::loop();
}