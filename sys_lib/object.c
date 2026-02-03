#include "object.h"

struct Object* allocate_obj(size_t size){
    struct Object* obj = malloc(sizeof(struct Object));
    obj->ref = 1;
    obj->object = malloc(size);
    return obj;
}

void decr_ref(struct Object* obj){
    obj->ref--;
    if (obj->ref == 0){
        free(obj->object);
        free(obj);
    }
}

void incr_ref(struct Object* obj){
    obj->ref++;
}