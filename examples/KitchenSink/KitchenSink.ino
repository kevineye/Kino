#include <SPI.h>
#include <KTask.h>
#include <KWiFi.h>
#include <KButton.h>
#include <KDisplay.h>

#define BUTTON_A 9
#define BUTTON_B 6
#define BUTTON_C 5

KDisplay display;

KWiFi wifi("abc", NULL);

char *defaultText = "Press a button...";

// handler for button A
void press_a(KButton *button) {
    Serial.println("Press: A");
    display.set("A");
}

void release_a(KButton *button) {
    Serial.println("Release: A");
    display.set(defaultText);
}

KButton buttonA(BUTTON_A, press_a, release_a);

// handler for button B
void press_b(KButton *button) {
    Serial.println("Press: B");
    display.set("B");
}

void release_b(KButton *button) {
    Serial.println("Release: B");
    display.set(defaultText);
}

KButton buttonB(BUTTON_B, press_b, release_b);

// handler for button C
void press_c(KButton *button) {
    Serial.println("Press: C");
    display.set("C");
}

void release_c(KButton *button) {
    Serial.println("Release: C");
    display.set(defaultText);
}

KButton buttonC(BUTTON_C, press_c, release_c);

void setup() {
    // initialize serial
    // while (!Serial);
    Serial.begin(9600);
    Serial.println("Press a button...");

    // initialize tasks
    KTask::setup();

    // initialize display
    display.set(defaultText);
}

void loop() {
    KTask::loop();
}