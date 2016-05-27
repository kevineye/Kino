#include "KTask.h"

#ifndef KWiFi_h
#define KWiFi_h

#define WINC_CS   8
#define WINC_IRQ  7
#define WINC_RST  4
#define WINC_EN   2

class KWiFi : protected KTask {
public:
    KWiFi(char *ssid, char *pass);

    static char *ssid;
    static char *pass;
    bool connected = false;
    bool connecting = false;

protected:
    virtual void init() override;

    virtual void run() override;
};

#endif

