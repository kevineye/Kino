#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#ifndef KDisplay_h
#define KDisplay_h

#define DISPLAY_BUFFER_SIZE 84

class KDisplay {
private:
    char buffer[DISPLAY_BUFFER_SIZE + 1];

public:
    static Adafruit_SSD1306 display;

    KDisplay();

    void setup(int delayMs = 750);

    void set(char *text = "");

    char *get();

    Adafruit_SSD1306 *getDisplay();
};

#endif

