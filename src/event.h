#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "lib/types.h"
#include "common.h"

typedef struct _event {
    /* event id */
    uint id;

    /* event value */
    void  *val;
} event_t;
#define MAKE_EVENT(i, v) (event_t){ .id = i, .val = (void*)v }

// typedef void(*receiver_t)(event_t *);
typedef struct _receiver {
    /*
     * incase receiver should have other values
     */

    void(*func)(struct _receiver *, event_t *);
} receiver_t;
#define MAKE_RECEIVER(f) (receiver_t){ .func = f } 

typedef struct _dispatcher {
    /* receiverse is 2d array:
     * [id] -> list of receivers for event `id`
     * [id][idx] -> ptr to receiver `idx` for event `id`
     */
    receiver_t***  receivers;

    /* array of counts for receivers
     * [id] -> count of receivers for event `id`
     */
    unsigned int* receivers_count;

    /*
     * highest `id` + 1
     */
    uint        count;
} dispatcher_t;



/*
 * params:
 *   (uint) size: size/count of receiver lists
 * 
 * return: (dispatcher_t*)
 *   pointer to new dispatcher struct
 */
dispatcher_t* dispatcher_new            (uint size);

/*
 * params:
 *   (dispatcher_t*) dispatcher: to add receiver to
 *   (uint)          id:         event id to add receiver for
 *   (receiver_t*)   receiver:   function to add to receivers for event $id
 */
void          dispatcher_add_receiver   (dispatcher_t *dispatcher, uint id, receiver_t *receiver);

/* 
 * params:
 *   (dispatcher_t*) dispatcher: to dispatch event to
 * 
 * return: (int)
 *   0 -> no error
 *   1 -> invalid/unknown event id
 */
int           dispatcher_dispatch_event (dispatcher_t *dispatcher, event_t e);

/*
 * params:
 *   (dispatcher_t*) dispatcher: dispatcher to free
 */
void          dispatcher_free           (dispatcher_t *dispatcher);

