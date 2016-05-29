#include "KDisplay.h"
#include <string.h>

Adafruit_SSD1306 KDisplay::display;

KDisplay::KDisplay(long d) {
    splashDelay = d;
    bufferLen = 0;
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
    strncpy(buffer, s, KDISPLAY_BUFFER_SIZE);
    bufferLen = strlen(buffer);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(buffer);
    display.display();
}

void KDisplay::clear() {
    buffer[0] = '\0';
    bufferLen = 0;
    display.clearDisplay();
    display.setCursor(0, 0);
}

void KDisplay::flush() {
    display.display();
}

size_t KDisplay::write(uint8_t c) {
    if (bufferLen < KDISPLAY_BUFFER_SIZE) {
        buffer[++bufferLen] = c;
        display.print((char) c);
        return 1;
    } else {
        return 0;
    }
}

char *KDisplay::get() {
    return buffer;
}
