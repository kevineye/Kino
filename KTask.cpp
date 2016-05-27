#include <Arduino.h>
#include "KTask.h"

#define _TASK_LTS_POINTER
#include <TaskScheduler.h>

Scheduler KTask_runner;
Task *KTask_tasks[MAX_TASKS];
int KTask::numTasks = 0;

KTask::KTask(unsigned long intervalMs, void (*callback)()) {
    id = KTask::numTasks++;
    KTask_tasks[id] = new Task(intervalMs, TASK_FOREVER, callback);
    KTask_tasks[id]->setLtsPointer(this);
}

void KTask::dispatch() {
    Task& t = KTask_runner.currentTask();
    KTask* kt = (KTask*) t.getLtsPointer();
    kt->run();
}

void KTask::run() {
}

void KTask::setup() {
    KTask_runner.init();
    for (int i = 0; i < KTask::numTasks; i++) {
        KTask_runner.addTask(*KTask_tasks[i]);
        KTask_tasks[i]->enable();
    }
}

void KTask::loop() {
    KTask_runner.execute();
}

