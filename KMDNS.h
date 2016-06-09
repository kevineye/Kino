#include "KTask.h"
#ifdef ARDUINO_ARCH_ESP8266
    #include <ESP8266mDNS.h>
#else
    #include <Adafruit_WiFiMDNSResponder.h>
#endif

#ifndef KMDNS_H
#define KMDNS_H


class KMDNS : protected KTask {
public:
    KMDNS(char *name);

    char name[256];
#ifndef ARDUINO_ARCH_ESP8266
    Adafruit_WiFiMDNSResponder mdnsResponder;
#endif

protected:
    virtual void init() override;

    virtual void run() override;
};

#endif
