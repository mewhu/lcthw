#ifndef _stack_h
#define _stack_h

#include <lcthw/list.h>
/*
 * Queue *Queue_create();
 * void Queue_destroy(Queue *queue);
 * void Queue_send(Queue *queue, void *data);
 * void *Queue_peek(Queue *queue);
 * int Queue_count(Queue* queue);
 * QUEUE_FOREACH(queue, cur)
 * void *Queue_recv(Queue* queue);
 */

typedef ListNode QueueMessage;
typedef List Queue;
#define Queue_create()      List_create()
#define Queue_destroy(A)    List_destroy(A)
#define Queue_send(A,B)     List_push(A,B)
#define Queue_peek(A)       List_first(A)
#define Queue_recv(A)       List_shift(A)
#define Queue_count(A)      List_count(A)
#define QUEUE_FOREACH(A,B)  QueueMessage  *B = NULL;  \
                            for(B = A->first; B != NULL; B = B->next)

#endif
