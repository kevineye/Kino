#include <Adafruit_WINC1500.h>

#ifndef KWiFi_h
#define KWiFi_h

#define WINC_CS   8
#define WINC_IRQ  7
#define WINC_RST  4
#define WINC_EN   2

class KWiFi {
public:
    KWiFi(char *ssid, char *pass);

    static char *ssid;
    static char *pass;

    static void setup();

    static void loop();
};

#endif

