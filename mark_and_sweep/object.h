#ifndef OBJECT_H
#define OBJECT_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct object object_t;
typedef struct vector vector_t;
typedef struct Virtual_Machine vm_t;

typedef enum object_type {
    INTEGER,
    FLOAT,
    STRING,
    VECTOR3,
    ARRAY,
} object_type;

typedef struct vector
{
    object_t *x;
    object_t *y;
    object_t *z;
} vector_t;

typedef struct array
{
    size_t size;
    object_t **elements;
} array_t;

typedef union object_data {
    int v_int;
    float v_float;
    char *v_string;
    vector_t v_vector3;
    array_t v_array;
} object_data;

typedef struct object {
    object_type type;
    object_data data;
    bool is_marked;
} object_t;

object_t *__new_integer__(int value);
object_t *__new_float__(float value);
object_t *__new_string__(char *value);
object_t *__new_vector3__(object_t *x, object_t *y, object_t *z);
object_t *__new_array__(size_t size);
bool     array_set(object_t *object, size_t index, object_t *value);
object_t *array_get(object_t *object, size_t index);
int      length(object_t *object);
object_t *__new_object__(vm_t *vm);
void    __free_object__(object_t *obj);


#endif
