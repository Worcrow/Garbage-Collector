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
    frame_t *new_frame= malloc(sizeof(frame_t));
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

void    vm_track_object(vm_t *vm, object_t *object)
{
    push(vm->object, object);
}

void    vm_free(vm_t *vm)
{
  _stack_t *frame = vm->frames;
  _stack_t *object = vm->object;

  for (size_t i = 0; i < frame->count; ++i)
  {
    frame_free(frame->data[i]);
  }
  __free_stack(frame);
  for (size_t i = 0; object->count; ++i)
  {
   __free_object__(object->data[i]); 
  }
  __free_stack(object);
  free(vm);
}

void  frame_reference_object(frame_t *frame, object_t *object)
{
  push(frame->references, object);
}

void  mark(vm_t *vm)
{
  _stack_t *frame = vm->frames;
  for (size_t i = 0; i < frame->count; ++i)
  {
    frame_t *reference = (frame_t *) frame->data[i];
    for (size_t j = 0; j < reference->references->count; ++j)
    {
      object_t *object = (object_t *) reference->references->data[j];
      object->is_marked = true;
    }
  }
}

void   trace_mark_object(_stack_t *gray_object, object_t *object)
{
  if (!object || object->is_marked)
    return ;
  object->is_marked = true;
  push(gray_object, object);
}

void   trace_blacken_object(_stack_t *gray_object, object_t *object)
{
   switch (object->type) {
    case INTEGER:
    case FLAOT:
    case STRING:
      break ;
    case VECTRO3:
      trace_mark_object(gray_object, object->data.v_vector3.x);
      trace_mark_object(gray_object, object->data.v_vector3.y);
      trace_mark_object(gray_object, object->data.v_vector3.z);
      break ;
    case ARRAY:
      {
        array_t *array = &object->data.v_array;
        for (size_t i = 0; i < array->size; ++i)
        {
          trace_mark_object(gray_object, array->elements[i]);
        }
      }
     break ;
   }
}

void  trace(vm_t *vm)
{
  _stack_t *gray_object = new_stack(8);
  _stack_t *object = vm->object;
  if (!gray_object)
    return ;
  for (size_t i = 0; i < object->count; ++i)
  {
    object_t *obj = (object_t *) object->data[i];
    if (obj->is_marked)
      push(gray_object, obj);
  }
  while (gray_object->count)
  {
    object_t *obj = (object_t *) pop(gray_object);
    trace_blacken_object(gray_object, obj);
  }
  __free_stack(gray_object);
}

void  sweep(vm_t *vm)
{
  _stack_t *object = vm->object;
  for (size_t i = 0; i < object->count; ++i)
  {
    object_t *obj = (object_t *) object->data[i];
    if (!obj->is_marked)
    {
      __free_object__(obj);
      object->data[i] = NULL;
    }
    else
       obj->is_marked = false;
  }
  stack_removes_null(object); 
}

void  vm_collect_garbage(vm_t *vm)
{
  mark(vm);
  trace(vm);
  sweep(vm);
}
