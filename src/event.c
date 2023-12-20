#include "event.h"


dispatcher_t* dispatcher_new(uint size) {
    dispatcher_t *dispatcher = calloc(1, sizeof(dispatcher_t));
    dispatcher->count = size;
    dispatcher->receivers = calloc(size, sizeof(receiver_t));
    dispatcher->receivers_count = calloc(size, sizeof(receiver_t));
    return dispatcher;
}

void dispatcher_free(dispatcher_t *dispatcher) {
    for (uint i=0; i < dispatcher->count; i++) {
        free(dispatcher->receivers[i]);
    }
    free(dispatcher->receivers_count);
    free(dispatcher->receivers);
    free(dispatcher);
}



void dispatcher_add_receiver(dispatcher_t *dispatcher, uint id, receiver_t receiver) {
    if (dispatcher->count < id) {
        dispatcher->receivers = realloc(dispatcher->receivers, (id+1) * sizeof(receiver_t*));
        dispatcher->receivers_count = realloc(dispatcher->receivers_count, (id+1) * sizeof(int));
        dispatcher->count = id;
    }

    uint count = ++dispatcher->receivers_count[id];
    dispatcher->receivers[id] = realloc(dispatcher->receivers[id], (count+1) * sizeof(receiver_t*));
    dispatcher->receivers[id][count - 1] = receiver;
}

int dispatcher_dispatch_event(dispatcher_t *dispatcher, event_t e) {
    if (dispatcher->count < e.id) {
        return 1;
    }

    for (uint i = 0; i < dispatcher->receivers_count[e.id]; i++) {
        dispatcher->receivers[e.id][i](&e);
    }
    return 0;
}
