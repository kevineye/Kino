#include <Arduino.h>
#include <Scheduler.h>
#include "KButton.h"

KButton::KButton(int buttonPin, void (*onPressCb)(KButton *), void (*onReleaseCb)(KButton *)) {
    pin = buttonPin;
    state = HIGH;
    pressed = state == LOW;
    lastValue = state;
    lastDebounceTime = 0;
    if (onPressCb) this->onPress(onPressCb);
    if (onReleaseCb) this->onRelease(onReleaseCb);
    buttons[numButtons++] = this;
}

KButton *KButton::buttons[MAX_BUTTONS];
int KButton::numButtons = 0;

void KButton::readOne() {
    int value = digitalRead(pin);
    if (value != lastValue) {
        lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > 10) {
        if (value != state) {
            state = value;
            pressed = state == LOW;
            if (pressCallback && pressed) pressCallback(this);
            if (releaseCallback && !pressed) releaseCallback(this);
        }
    }
    lastValue = value;
}

void KButton::setupOne() {
    pinMode(pin, INPUT_PULLUP);
    state = digitalRead(pin);
}

void KButton::readAll() {
    for (int i = 0; i < KButton::numButtons; i++) {
        KButton::buttons[i]->readOne();
    }
}

void KButton::loop() {
    KButton::readAll();
    delay(5);
}

void KButton::onPress(void (*cb)(KButton *)) {
    pressCallback = cb;
}

void KButton::onRelease(void (*cb)(KButton *)) {
    releaseCallback = cb;
}

void KButton::setup() {
    for (int i = 0; i < KButton::numButtons; i++) {
        KButton::buttons[i]->setupOne();
    }
    Scheduler.start(NULL, KButton::loop);
}
