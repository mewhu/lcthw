#ifndef _stack_h
#define _stack_h

#include <lcthw/list.h>
/*
 * Stack *Stack_create();
 * void Stack_destroy(Stack *stack);
 * void Stack_push(Stack *stack, void *data);
 * void *Stack_peek(Stack *stack);
 * int Stack_count(Stack* stack);
 * STACK_FOREACH(stack, cur)
 * void *Stack_pop(Stack* stack);
 */

typedef ListNode StackElement;
typedef List Stack;

#define Stack_create()      List_create()
#define Stack_destroy(A)    List_destroy(A)
#define Stack_push(A,B)     List_push(A,B)
#define Stack_peek(A)       List_last(A)
#define Stack_pop(A)        List_pop(A)
#define Stack_count(A)      List_count(A)
#define STACK_FOREACH(A,B)  StackElement *B=NULL;  \
                            for(B = A->last; B != NULL; B = B->prev)


#endif
