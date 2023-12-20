#include <stdio.h>
#include <stdlib.h>

#include "lib/types.h"
#include "common.h"

#include "event.h"


enum {
    test_event_1 = 0,
    test_event_2,
};
void test_receiver(event_t *event) {
    printf("---< EVENT RECEIVER 1 >---\n");
    printf(" |> id: %d\n", event->id);
    printf(" |> val: %s\n", (char*)event->val);
}
void test_receiver_2(event_t *event) {
    printf("---< EVENT RECEIVER 2 >---\n");
    printf(" |> id: %d\n", event->id);
    printf(" |> val: 0x%x\n", (uint)event->val);
}


int main(void) {
    dispatcher_t *dispatcher = dispatcher_new(0);

    dispatcher_add_receiver(dispatcher, test_event_1, test_receiver);
    dispatcher_add_receiver(dispatcher, test_event_2, test_receiver_2);


    int e;
    e = dispatcher_dispatch_event(dispatcher, (event_t)MAKE_EVENT(test_event_1, "hello"));
    if (e != 0) {
        printf("dispatching event (%d) failed: %d\n", test_event_1, e);
    }
    e = dispatcher_dispatch_event(dispatcher, (event_t)MAKE_EVENT(test_event_2, 0x42069));
    if (e != 0) {
        printf("dispatching event (%d) failed: %d\n", test_event_2, e);
    }

    goto cleanup;
cleanup:
    dispatcher_free(dispatcher);
    return 0;
}
