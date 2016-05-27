#include "KTask.h"
#include <Arduino.h>

#ifndef KEvent_h
#define KEvent_h

#define KEVENT_MAX_LISTENERS   64

class KEvent {
public:
    KEvent(long type, void *eventData);

    int type;
    void *data;

    static void on(long type, void (*callback)(KEvent, void *), void *callbackData = NULL);

    static void emit(KEvent event);

    static void emit(long type);

    static void emit(long type, void *eventData = NULL);
};

#endif

