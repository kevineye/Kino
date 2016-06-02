#include "KWatchdog.h"
#include <Adafruit_SleepyDog.h>

KWatchdog::KWatchdog(int t) : KTask(1000) {
    timeout = t;
}

void KWatchdog::init() {
    timeout = Watchdog.enable(timeout);
}

void KWatchdog::run() {
    Watchdog.reset();
}
