#include <SPI.h>
#include <KTask.h>
#include <KWiFi.h>
#include <KHttpServer.h>
#include <KEvent.h>

#define LEDPIN LED_BUILTIN

KWiFi wifi("ssid", "password");
KHttpServer server(80);

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
