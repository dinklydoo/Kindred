#ifndef OBJECT_H
#define OBJECT_H

#include <stdlib.h>

struct Object {
    int ref; // reference count
    void* object;
};

void decr_ref(struct Object* obj);
void incr_ref(struct Object* obj);
struct Object* allocate_obj(size_t size);

#endif