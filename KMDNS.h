#include "KTask.h"
#include <ArduinoHttpServer.h>
#include <Adafruit_WINC1500.h>

#ifndef KHTTPSERVER_H
#define KHTTPSERVER_H

#define KEVENT_HTTPSERVER_REQUEST         0x00002001

typedef Adafruit_WINC1500Server KHttpServerImpl;
typedef Adafruit_WINC1500Client KHttpClient;
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
