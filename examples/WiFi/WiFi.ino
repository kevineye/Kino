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
    display.clear();
    display.print("Connected to ");
    display.println(wifi.wifi->SSID());
    display.print("IP: ");
    IPAddress ip = wifi.wifi->localIP();
    display.println(ip);
    display.print("Signal: ");
    display.print(wifi.wifi->RSSI());
    display.println(" dBm");
    display.flush();
};

void failed(KEvent event, void *callbackData) {
    display.clear();
    display.println("Connection failed to");
    display.println(wifi.ssid);
    display.flush();
};

void connecting(KEvent event, void *callbackData) {
    display.clear();
    display.print("Attempting to connect\nto ");
    display.println(wifi.ssid);
    display.flush();
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