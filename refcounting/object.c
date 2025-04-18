#include "object.h"

object_t *__new_integer__(int value) {
    object_t *new_int = malloc(sizeof(object_t));
    if (!new_int)
        return (NULL);
    new_int->type = INTEGER;
    new_int->data.v_int = value;
    return (new_int);
}

object_t *__new_float__(float value) {
    object_t *new_float = malloc(sizeof(object_t));
    if (!new_float)
        return (NULL);
    new_float->type = FLOAT;
    new_float->data.v_float = value;
    return (new_float);
}

object_t *__new_string__(char *value) {
    object_t *new_string = malloc(sizeof(object_t));
    if (!new_string)
        return (NULL);
    new_string->type = STRING;
    new_string->data.v_string = strdup(value);
    if (!new_string->data.v_string) {
        free(new_string);
        return (NULL);
    }
    return (new_string);
}

object_t *__new_vector3__(object_t *x, object_t *y, object_t *z)
{
    if (!x || !y || !z)
        return (NULL);
    object_t *new_object = malloc(sizeof(object_t));
    if (!new_object)
        return (NULL);
    new_object->type = VECTOR3;
    refCount_inc(x);
    refCount_inc(y);
    refCount_inc(z);
    new_object->data.v_vector3 = (vector_t){x, y, z};
    return (new_object);
}

object_t *__new_array__(size_t size)
{
    object_t *new_array = malloc(sizeof(object_t));
    if (!new_array)
        return (NULL);
    object_t **array = calloc(size, sizeof(object_t));
    if (!array)
    {
        free(new_array);
        return (NULL);
    }
    new_array->type = ARRAY;
    new_array->data.v_array.size = size;
    new_array->data.v_array.elements = array;
    return (new_array);
}
bool     array_set(object_t *object, size_t index, object_t *value)
{
    if (!object || !value || object->type != ARRAY \
        || object->data.v_array.size <= index)
        return (false);
    refCount_dec(object->data.v_array.elements[index]);
    refCount_inc(value);
    object->data.v_array.elements[index] = value;;
    return (true);
}

object_t *array_get(object_t *object, size_t index)
{
    if (!object || object->type != ARRAY || object->data.v_array.size <= index)
        return (NULL);
    return (object->data.v_array.elements[index]);
}

int      length(object_t *object)
{
    if (!object || !object->type)
        return (-1);
    else if (object->type == INTEGER || object->type == FLOAT)
        return (1);
    else if (object->type == VECTOR3)
        return (3);
    else if (object->type == STRING && object->data.v_string != NULL)
        return (strlen(object->data.v_string));
    else if (object->type == ARRAY)
        return (object->data.v_array.size);
    else
        return (-1);
}

object_t *__new_object__()
{
    object_t *new_object = calloc(1, sizeof(object_t));
    if (!new_object)
        return (NULL);
    new_object->refcount = 1;
    return (new_object);
}

void    refCount_inc(object_t *object)
{
    if (!object)
        return ;
    object->refcount += 1;
}

void    refCount_dec(object_t *object)
{
    if (!object)
        return ;
    object->refcount -= 1;
    if (object->refcount == 0)
        return (refCount_free(object));
}

void    refCount_free(object_t *object)
{
    if (object->type == INTEGER || object->type == FLOAT)
        free(object);
    else if (object->type == STRING)
    {
        free(object->data.v_string);
        free(object);
    }
    else if (object->type == VECTOR3)
    {
        refCount_dec(object->data.v_vector3.x);
        refCount_dec(object->data.v_vector3.y);
        refCount_dec(object->data.v_vector3.z);
    }
    else if (object->type == ARRAY)
    {
        for (size_t i = 0; i < object->data.v_array.size; i++)
        {
            refCount_dec(object->data.v_array.elements[i]);
        }
        free(object->data.v_array.elements);
    }
}
