#ifndef MyButton_h
#define MyButton_h

#define MAX_BUTTONS 16

class MyButton {
  private:
    static MyButton* buttons[MAX_BUTTONS];
    static int numButtons;
    int pin;
    int lastValue;
    unsigned long lastDebounceTime;
    void (*pressCallback)(MyButton*);
    void (*releaseCallback)(MyButton*);
    void readOne();
    void setupOne();
    static void readAll();
    static void loop();
  public:
    MyButton(int pin, void (*onPress)(MyButton*)=NULL, void (*onRelease)(MyButton*)=NULL);
    String label;
    int state;
    bool pressed;
    static void setup();
    void onPress(void (*cb)(MyButton*));
    void onRelease(void (*cb)(MyButton*));
};

#endif
