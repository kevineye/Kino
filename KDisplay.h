#include "KTask.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#ifndef KDisplay_h
#define KDisplay_h

#define DISPLAY_BUFFER_SIZE 84

class KDisplay : protected KTask {
private:
    char buffer[DISPLAY_BUFFER_SIZE + 1];
    long splashDelay;

public:
    static Adafruit_SSD1306 display;

    KDisplay(long splashDelay = 750);

    void set(char *text = "");

    char *get();

protected:
    virtual void init() override;
};

#endif

