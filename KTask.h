#ifndef KTask_h
#define KTask_h

#define MAX_TASKS 32

class KTask {
private:
    static int numTasks;
    static void dispatch();
    int id;

public:
    KTask(unsigned long intervalMs, void (*callback)() = KTask::dispatch);

    static void loop();

    static void setup();

    void run();
};

#endif
