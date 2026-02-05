#include "object.h"

object* allocate_obj(size_t size){
    object* ptr = (object*)malloc(sizeof(object));
    ptr->obj = malloc(size);
    ptr->ref = 1;
    return ptr;
}

void decr_obj(object *obj){
    obj->ref--;
    if (obj->ref == 0){
        free(obj->obj);
        free(obj);
    }
}

void incr_obj(object *obj){
    obj->ref++;
}