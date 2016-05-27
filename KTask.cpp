#include <Arduino.h>
#include "KTask.h"

#define _TASK_LTS_POINTER

#include <TaskScheduler.h>

Scheduler KTask_runner;
Task *KTask_tasks[MAX_TASKS];
KTask *KTask_ktasks[MAX_TASKS];
int KTask::numTasks = 0;

KTask::KTask(long interval, void (*callback)()) {
    // use interval=-1 (default) for setup-only tasks
    id = KTask::numTasks++;
    if (interval >= 0) {
        KTask_tasks[id] = new Task(interval, TASK_FOREVER, callback);
        KTask_tasks[id]->setLtsPointer(this);
    } else {
        KTask_tasks[id] = NULL;
    }
    KTask_ktasks[id] = this;
}

void KTask::dispatch() {
    Task &t = KTask_runner.currentTask();
    KTask *kt = (KTask *) t.getLtsPointer();
    kt->run();
}

void KTask::init() {
//    Serial.print("In base init of task ");
//    Serial.println(id);
}

void KTask::run() {
//    Serial.print("In base run of task ");
//    Serial.println(id);
}

void KTask::setup() {
    KTask_runner.init();
    for (int i = 0; i < KTask::numTasks; i++) {
        if (KTask_tasks[i]) {
            KTask_runner.addTask(*KTask_tasks[i]);
            KTask_tasks[i]->enable();
        }
        KTask_ktasks[i]->init();
    }
}

void KTask::loop() {
    KTask_runner.execute();
}

