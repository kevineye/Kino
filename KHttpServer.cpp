#include "KHttpServer.h"
#include "KEvent.h"
#include "KWiFi.h"

KHttpServer::KHttpServer(int p) : KTask(10) {
    port = p;
    server = KHttpServerImpl(port);
}

void KHttpServer_on_wifi_connect(KEvent event, void *callbackData) {
    KHttpServer *kserver = (KHttpServer *) callbackData;
    kserver->server.begin();
}

void KHttpServer::init() {
    KEvent::on(KEVENT_WIFI_CONNECT, KHttpServer_on_wifi_connect, this);
}

void KHttpServer::run() {
    KHttpClient client(server.available());
    if (client.connected()) {
        KHttpRequest httpRequest(client);
        if (httpRequest.readRequest()) {
            KEvent::emit(KEVENT_HTTPSERVER_REQUEST, &httpRequest);
            client.stop();
        } else {
            ArduinoHttpServer::StreamHttpErrorReply httpReply(client, httpRequest.getContentType());
            httpReply.send(httpRequest.getErrorDescrition());
        }
    }
}
