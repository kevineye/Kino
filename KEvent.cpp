#include "KEvent.h"

KEvent::KEvent(long t, void *d) {
    type = t;
    data = d;
}

struct KEvent_Listener {
    long type;

    void (*callback)(KEvent, void *);

    void *callbackData;
};

KEvent_Listener KEvent_listeners[KEVENT_MAX_LISTENERS];
int KEvent_numListeners = 0;

void KEvent::on(long type, void (*callback)(KEvent, void *), void *callbackData) {
    KEvent_listeners[KEvent_numListeners].type = type;
    KEvent_listeners[KEvent_numListeners].callback = callback;
    KEvent_listeners[KEvent_numListeners].callbackData = callbackData;
    KEvent_numListeners++;
}

void KEvent::emit(KEvent event) {
    for (int i = 0; i < KEvent_numListeners; i++) {
        if (KEvent_listeners[i].type == event.type) {
            KEvent_listeners[i].callback(event, KEvent_listeners[i].callbackData);
        }
    }
}

void KEvent::emit(long type, void *data) {
    KEvent event(type, data);
    KEvent::emit(event);
}

