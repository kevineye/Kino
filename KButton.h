#ifndef KButton_h
#define KButton_h

#define MAX_BUTTONS 16

class KButton {
private:
    static KButton *buttons[MAX_BUTTONS];
    static int numButtons;
    int pin;
    int lastValue;
    unsigned long lastDebounceTime;

    void (*pressCallback)(KButton *);

    void (*releaseCallback)(KButton *);

    void readOne();

    void setupOne();

    static void readAll();

    static void loop();

public:
    KButton(int pin, void (*onPress)(KButton *) = NULL, void (*onRelease)(KButton *) = NULL);

    String label;
    int state;
    bool pressed;

    static void setup();

    void onPress(void (*cb)(KButton *));

    void onRelease(void (*cb)(KButton *));
};

#endif
