#ifndef OBJECT_H
#define OBJECT_H

#include <stdlib.h>

typedef struct object {
    int ref; // reference count
    void* obj;
} object;

void decr_obj(object* obj);
void incr_obj(object* obj);
object* allocate_obj(size_t size);

#endif