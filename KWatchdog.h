#include "KTask.h"

#ifndef KWATCHDOG_H
#define KWATCHDOG_H

class KWatchdog : protected KTask {
public:
    KWatchdog(int desiredTimeout = 15000);
    int timeout;

protected:
    virtual void init() override;

    virtual void run() override;
};

#endif

