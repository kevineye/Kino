#include <Arduino.h>
#include <Scheduler.h>
#include "MyButton.h"

MyButton::MyButton(int buttonPin, void (*onPressCb)(MyButton*), void (*onReleaseCb)(MyButton*)) {
  pin = buttonPin;
  pinMode(pin, INPUT_PULLUP);
  state = digitalRead(pin);
  pressed = state == LOW;
  lastValue = state;
  lastDebounceTime = 0;
  if (onPressCb) this->onPress(onPressCb);
  if (onReleaseCb) this->onRelease(onReleaseCb);
  buttons[numButtons++] = this;
}

MyButton* MyButton::buttons[MAX_BUTTONS];
int MyButton::numButtons = 0;

void MyButton::read() {
  int value = digitalRead(pin);
  if (value != lastValue) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > 10) {
    if (value != state){
      state = value;
  	  pressed = state == LOW;
      if (pressCallback && pressed) pressCallback(this);
      if (releaseCallback && !pressed) releaseCallback(this);
    }
  }
  lastValue = value;
}

void MyButton::readAll() {
  for (int i = 0; i < MyButton::numButtons; i++) {
    MyButton::buttons[i]->read();
  }
}

void MyButton::loop() {
  MyButton::readAll();
  delay(5);
}

void MyButton::onPress(void (*cb)(MyButton*)) {
  pressCallback = cb;
}

void MyButton::onRelease(void (*cb)(MyButton*)) {
  releaseCallback = cb;
}

void MyButton::setup() {
  Scheduler.start(NULL, MyButton::loop);
}
