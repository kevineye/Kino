#include "KTask.h"
#include <Adafruit_WiFiMDNSResponder.h>

#ifndef KMDNS_H
#define KMDNS_H

class KMDNS : protected KTask {
public:
    KMDNS(char *name);

    char name[256];
    Adafruit_WiFiMDNSResponder mdnsResponder;

protected:
    virtual void init() override;

    virtual void run() override;
};

#endif
