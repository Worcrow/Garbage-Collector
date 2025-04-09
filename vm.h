#ifndef __VIRTUAL_MACHINE__H
#define __VIRTUAL_MACHINE__H

#include "stack.h"

typedef struct Virtula_Machine {
    _stack_t *frames; //hold stack frames,
    _stack_t *object; //hold object pointers
} vm_t;

vm_t*    __vm_new__();
void    __vm_free__(vm_t *vm);

#endif
