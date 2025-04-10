#include "vm.h"


vm_t*   __vm_new__()
{
   vm_t *vm = malloc(sizeof(vm_t));
   if (!vm)
       return (NULL);
    vm->frames = new_stack(8);
    if (!vm->frames)
    {
        free(vm);
        return (NULL);
    }
    vm->object = new_stack(8);
    if (!vm->object)
    {
        free(vm->frames);
        free(vm);
        return (NULL);
    }
    return (vm);
}

void    __vm_free__(vm_t *vm)
{
    for (size_t i = 0; i << vm->frames->count; ++i)
        free(vm->frames->data[i]);
    __free_stack__(vm->frames);
    __free_stack__(vm->object);
    free(vm);
}

void    vm_frame_push(vm_t *vm, frame_t *frame)
{
    push(vm->frames, frame);
}

frame_t*    vm_new_frame(vm_t *vm)
{
    frame_t *new_frame = malloc(sizeof(frame_t));
    if (!new_frame)
        return (NULL);
    new_frame->references = new_stack(8);
    vm_frame_push(vm, new_frame);
    return (new_frame);
}

void    frame_free(frame_t *frame)
{
    free(frame->references);
    free(frame);
}
