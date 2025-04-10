#ifndef __VIRTUAL_MACHINE__H
#define __VIRTUAL_MACHINE__H

#include "stack.h"

typedef struct Virtula_Machine {
    _stack_t *frames; //hold stack frames,
    _stack_t *object; //hold object pointers
} vm_t;

typedef struct Stack_frame
{
    _stack_t *references;
}   frame_t;

vm_t*    __vm_new__();
void    __vm_free__(vm_t *vm);
void    vm_frame_push(vm_t *vm, frame_t *frame);
frame_t* vm_new_frame(vm_t *vm);
void    frame_free(frame_t *);


#endif
