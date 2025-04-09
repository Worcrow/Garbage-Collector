#ifndef __STACK__H
#define __STACK__H

#include <stdlib.h>

typedef struct stack {
    size_t count;
    size_t capacity;
    void   **data;
} _stack_t;

stack_t *__new_stack__(size_t capacity);

void push(_stack_t *stack, void *data);
void *pop(_stack_t *stack);

void __free_stack__(_stack_t *stack);
void stack_removes_nulls(_stack_t *stack);
_stack_t *new_stack(size_t capacity);
#endif
