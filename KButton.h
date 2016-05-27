#include "KTask.h"

#ifndef KButton_h
#define KButton_h

#define MAX_BUTTONS 16

class KButton : protected KTask {
private:
    int pin;
    int lastValue;
    unsigned long lastDebounceTime;

    void (*pressCallback)(KButton *);

    void (*releaseCallback)(KButton *);

public:
    KButton(int pin, void (*onPress)(KButton *) = NULL, void (*onRelease)(KButton *) = NULL);

    String label;
    int state;
    bool pressed;

    void onPress(void (*cb)(KButton *));

    void onRelease(void (*cb)(KButton *));

protected:
    virtual void init() override;

    virtual void run() override;

};

#endif
