#include <KTask.h>
#include <KWiFi.h>
#include <KHttpServer.h>
#include <KMDNS.h>
#include <KEvent.h>
#include <KDisplay.h>

KDisplay display;
KWiFi wifi("ssid", "pass");
KHttpServer server(80);
KMDNS mdns("feather");

void disconnect(KEvent event, void *callbackData) {
    display.set("Disconnected");
};

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

void request(KEvent event, void *callbackData) {
    KHttpRequest *request = (KHttpRequest *) event.data;
    display.clear();
    ArduinoHttpServer::MethodEnum method(ArduinoHttpServer::MethodInvalid);
    method = request->getMethod();
    if (method == ArduinoHttpServer::MethodGet) {
        display.print("GET");
    }
    else if (method == ArduinoHttpServer::MethodPost) {
        display.print("POST");
    }
    display.print(" ");
    display.println(request->getResource().toString());
    display.flush();
    ArduinoHttpServer::StreamHttpReply httpReply(request->getStream(), "application/json");
    httpReply.send("{\"foo\":\"bar\"}");
};

void setup() {
    KTask::setup();
    KEvent::on(KEVENT_WIFI_CONNECT, connect);
    KEvent::on(KEVENT_WIFI_CONNECTING, connecting);
    KEvent::on(KEVENT_WIFI_CONNECT_FAILED, failed);
    KEvent::on(KEVENT_WIFI_DISCONNECT, disconnect);
    KEvent::on(KEVENT_HTTPSERVER_REQUEST, request);
}

void loop() {
    KTask::loop();
}