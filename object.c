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
    new_object->data.v_vector3 = (vector_t){x, y, z};
    return (new_object);
}

