#include "KDisplay.h"
#include <string.h>

Adafruit_SSD1306 KDisplay::display;

KDisplay::KDisplay() {
//    display = Adafruit_SSD1306();
}

void KDisplay::setup(int delayMs) {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display();
    delay(delayMs);
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

Adafruit_SSD1306 *KDisplay::getDisplay() {
    return &display;
}