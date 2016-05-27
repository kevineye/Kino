#include <Arduino.h>
#include "KButton.h"

KButton::KButton(int buttonPin, void (*onPressCb)(KButton *), void (*onReleaseCb)(KButton *)) : KTask(5) {
    pin = buttonPin;
    state = HIGH;
    pressed = state == LOW;
    lastValue = state;
    lastDebounceTime = 0;
    if (onPressCb) this->onPress(onPressCb);
    if (onReleaseCb) this->onRelease(onReleaseCb);
}

void KButton::run() {
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

void KButton::init() {
    pinMode(pin, INPUT_PULLUP);
    state = digitalRead(pin);
}

void KButton::onPress(void (*cb)(KButton *)) {
    pressCallback = cb;
}

void KButton::onRelease(void (*cb)(KButton *)) {
    releaseCallback = cb;
}
