#ifndef KTask_h
#define KTask_h

#define MAX_TASKS 32

class KTask {
private:
    int id;

public:
    KTask(unsigned long intervalMs, void (*callback)());

    static void loop();

    static void setup();
};

#endif
