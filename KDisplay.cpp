#include "KDisplay.h"
#include <string.h>

Adafruit_SSD1306 KDisplay::display;

KDisplay::KDisplay(long d) {
    splashDelay = d;
}

void KDisplay::init() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display();
    delay(splashDelay);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.clearDisplay();
    display.display();
}

void KDisplay::set(char *s) {
    strncpy(buffer, s, DISPLAY_BUFFER_SIZE);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(s);
    display.display();
}

char *KDisplay::get() {
    return buffer;
}
