#include "KWatchdog.h"
#ifndef ARDUINO_ARCH_ESP8266
    #include <Adafruit_SleepyDog.h>
#endif

#ifdef ARDUINO_ARCH_ESP8266
KWatchdog::KWatchdog(int t) : KTask(-1) {
#else
KWatchdog::KWatchdog(int t) : KTask(1000) {
#endif
    timeout = t;
}

void KWatchdog::init() {
#ifndef ARDUINO_ARCH_ESP8266
    timeout = Watchdog.enable(timeout);
#endif
}

void KWatchdog::run() {
#ifndef ARDUINO_ARCH_ESP8266
    Watchdog.reset();
#endif
}
