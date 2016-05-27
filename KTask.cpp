#include <Arduino.h>
#include "KTask.h"

#include <TaskScheduler.h>

Scheduler runner;
Task *tasks[MAX_TASKS];
int numTasks = 0;

KTask::KTask(unsigned long intervalMs, void (*callback)()) {
    id = numTasks++;
    tasks[id] = new Task(intervalMs, TASK_FOREVER, callback);
}

void KTask::setup() {
    runner.init();
    for (int i = 0; i < numTasks; i++) {
        runner.addTask(*tasks[i]);
        tasks[i]->enable();
    }
}

void KTask::loop() {
    runner.execute();
}

