#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lib/types.h"
#include "common.h"

#include "event.h"


enum {
    test_event_1 = 0,
    test_event_2,
};
void test_receiver(receiver_t *this, event_t *event) {
    printf("---< EVENT RECEIVER 1 >---\n");
    printf(" |> id: %d\n", event->id);
    printf(" |> val: %s\n", (char*)event->val);
    printf(" |> this: %p\n", this);
}
void test_receiver_2(receiver_t *this, event_t *event) {
    printf("---< EVENT RECEIVER 2 >---\n");
    printf(" |> id: %d\n", event->id);
    printf(" |> val: 0x%x\n", (uint)event->val);
    printf(" |> this: %p\n", this);
}


int main(void) {
    dispatcher_t *dispatcher = dispatcher_new(0);

    receiver_t receiver_1 = MAKE_RECEIVER(test_receiver);
    receiver_t receiver_2 = MAKE_RECEIVER(test_receiver_2);

    dispatcher_add_receiver(dispatcher, test_event_1, &receiver_1);
    dispatcher_add_receiver(dispatcher, test_event_2, &receiver_2);

    srand(time(NULL));
    for (int i=0; i < 10; i++) {
        int e;

        bool r = ((int)(rand() * 0.1) % 10) > 5;
        if (r)  e = dispatcher_dispatch_event(dispatcher, MAKE_EVENT(test_event_1, "Hello"));
        else    e = dispatcher_dispatch_event(dispatcher, MAKE_EVENT(test_event_2, 0x69420));

        if (e != 0) {
            printf("dispatching event (%d) failed: %d\n", r, e);
        }
    }

    goto cleanup;
cleanup:
    dispatcher_free(dispatcher);
    return 0;
}
