#include <stdio.h>
#include <stdlib.h>

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

    dispatcher_add_receiver(dispatcher, test_event_1, &MAKE_RECEIVER(test_receiver));
    dispatcher_add_receiver(dispatcher, test_event_2, &MAKE_RECEIVER(test_receiver_2));


    int e;
    e = dispatcher_dispatch_event(dispatcher, MAKE_EVENT(test_event_1, "hello"));
    if (e != 0) {
        printf("dispatching event (%d) failed: %d\n", test_event_1, e);
    }
    e = dispatcher_dispatch_event(dispatcher, MAKE_EVENT(test_event_2, 0x42069));
    if (e != 0) {
        printf("dispatching event (%d) failed: %d\n", test_event_2, e);
    }

    goto cleanup;
cleanup:
    dispatcher_free(dispatcher);
    return 0;
}
