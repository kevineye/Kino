#include "KTask.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#ifndef KDisplay_h
#define KDisplay_h

#define KDISPLAY_BUFFER_SIZE 84

class KDisplay : protected KTask, public Print {
private:
    char buffer[KDISPLAY_BUFFER_SIZE + 1];
    size_t bufferLen;
    long splashDelay;

public:
    static Adafruit_SSD1306 display;

    KDisplay(long splashDelay = 750);

    void set(char *text = "");

    char *get();

    size_t write(uint8_t c) override;

    // make sure to call flush after print()ing or clear()ing
    // not necessary after set()
    void flush();

    // use clear() instead of set("") to clear without actually blanking the screen
    void clear();

protected:
    virtual void init() override;
};

#endif

