#ifndef __VIRTUAL_MACHINE__H
#define __VIRTUAL_MACHINE__H

#include "stack.h"
#include "object.h"

typedef struct Virtual_Machine {
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
void    vm_track_object(vm_t *vm, object_t *obj);
void    vm_free(vm_t *vm);
void  frame_reference_object(frame_t *frame, object_t *object);
void  mark(vm_t *vm);
void   trace_mark_object(_stack_t *gray_object, object_t *object);
void   trace_blacken_object(_stack_t *gray_object, object_t *object);
void  trace(vm_t *vm);
void  sweep(vm_t *vm);
void  vm_collect_garbage(vm_t *vm);


#endif
