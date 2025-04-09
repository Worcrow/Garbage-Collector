#include "stack.h"

void push(_stack_t *stack, void *data)
{
    if (stack->capacity == stack->count)
    {
        stack->capacity *= 2;
        stack->data = realloc(stack->data, stack->capacity * sizeof(void *));
        if (!stack->data)
            exit(1);
    }
    stack->data[stack->count] = data;
    stack->count++;
}

void *pop(_stack_t *stack)
{
    if (stack->count == 0)
        return (NULL);
    stack->count--;
    return (stack->data[stack->count]);
}

void __free_stack__(_stack_t *stack)
{
    if (stack == NULL)
        return ;
    if (stack->data != NULL)
        free(stack->data);
    free(stack);
}

void    stack_removes_null(_stack_t *stack)
{
    size_t new_size = 0;
    for (int i = 0; i < stack->count; ++i)
    {
        if (stack->data[i] != NULL)
            stack->data[new_size++] = stack->data[i];
    }
    stack->count = new_size;
    for (int i = stack->count; i < stack->capacity; ++i)
    {
        stack->data[i] = NULL;
    }
}

_stack_t *new_stack(size_t capacity)
{
    _stack_t *stack = malloc(sizeof(_stack_t));
    if (!stack)
        return (NULL);
    stack->count = 0;
    stack->capacity = capacity;
    stack->data = malloc(capacity * sizeof(void *));
    if (!stack->data)
    {
        free(stack);
        return (NULL);
    }
    return (stack);
}
