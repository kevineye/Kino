#include "KTask.h"
#include <ArduinoHttpServer.h>
#ifdef ARDUINO_ARCH_ESP8266
    #include <WiFiClient.h>
    #include <WiFiServer.h>
#else
    #include <Adafruit_WINC1500.h>
#endif

#ifndef KHTTPSERVER_H
#define KHTTPSERVER_H

#define KEVENT_HTTPSERVER_REQUEST         0x00002001

#ifdef ARDUINO_ARCH_ESP8266
    typedef WiFiServer KHttpServerImpl;
    typedef WiFiClient KHttpClient;
#else
    typedef Adafruit_WINC1500Server KHttpServerImpl;
    typedef Adafruit_WINC1500Client KHttpClient;
#endif
typedef ArduinoHttpServer::StreamHttpRequest<1023> KHttpRequest;

class KHttpServer : protected KTask {
public:
    KHttpServer(int port);

    int port;
    KHttpServerImpl server = NULL;

protected:
    virtual void init() override;

    virtual void run() override;
};


#endif
