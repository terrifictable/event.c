# event.c

simple events in c


an event is a struct containing two values:
``` c
int id;
void* val;
```

id is a way to identify events<br>
and val is a void pointer aka anything you want


## examples
the following example shows how you can create a dispatcher, event listener, add the listener to the dispatcher and how to dispatch an event
``` c
enum {
    test_event = 0,
};

void receiver(event_t *event) {
    printf("---<  RECEIVER  >---\n");
    printf("id: %d\n", event->id);
    printf("value: 0x%x\n", (unsigned int)event->val);
}

int main(void) {
    dispatcher_t *dispatcher = dispatcher_new(0);
    
    dispatcher_add_receiver(dispatcher, test_event, test_receiver);

    int e;
    if ((e = dispatcher_dispatch_event(dispatcher, MAKE_EVENT(test_event, 0x12345))) != 0) {
        printf("[ ERROR ]  failed to dispatch event, error: %d\n", e);
    }

    dispatcher_free(dispatcher);
    return 0;    
}
```
