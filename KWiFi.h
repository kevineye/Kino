#include "KTask.h"

#ifndef KWiFi_h
#define KWiFi_h

#define WINC_CS   8
#define WINC_IRQ  7
#define WINC_RST  4
#define WINC_EN   2

#define KEVENT_WIFI_CONNECT         0x00001001
#define KEVENT_WIFI_CONNECTING      0x00001002
#define KEVENT_WIFI_CONNECT_FAILED  0x00001003
#define KEVENT_WIFI_DISCONNECT      0x00001004

#define KWIFI_SERIAL_STATUS 1

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

