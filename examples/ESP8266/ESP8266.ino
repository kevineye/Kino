#include <SPI.h>
#include <KTask.h>
#include <KWiFi.h>

#define LEDPIN LED_BUILTIN

KWiFi wifi("ssid", "pass");

bool ledOn = false;
void blink() {
    if (ledOn) {
        digitalWrite(LEDPIN, LOW);
        Serial.println("on");
        ledOn = false;
    } else {
        digitalWrite(LEDPIN, HIGH);
        Serial.println("off");
        ledOn = true;
    }
}

KTask blinker(500, blink);

void setup() {
    Serial.begin(74880);
    pinMode(LEDPIN, OUTPUT);
    Serial.println("starting");
    KTask::setup();
}

void loop() {
    KTask::loop();
}

//#define LED LED_BUILTIN
//
//// the setup function runs once when you press reset or power the board
//void setup() {
//    // initialize digital pin 13 as an output.
//    Serial.begin(74880);
//    pinMode(LED, OUTPUT);
//}
//
//// the loop function runs over and over again forever
//void loop() {
//    digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
//    Serial.println("off");
//    delay(1000);              // wait for a second
//    digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
//    Serial.println("on");
//    delay(1000);              // wait for a second
//}