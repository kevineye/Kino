#ifndef KTask_h
#define KTask_h

#define MAX_TASKS 32

class KTask {
private:
    static int numTasks;

    static void dispatch();

    int id;

public:
    KTask(long interval = -1, void (*callback)() = KTask::dispatch);

    static void loop();

    static void setup();

protected:
    virtual void init();

    virtual void run();
};

#endif
