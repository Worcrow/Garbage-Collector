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
    __free_stack__(vm->frames);
    __free_stack__(vm->object);
    free(vm);
}
