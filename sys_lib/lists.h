#ifndef LISTS_H
#define LISTS_H

#include "object.h"

struct list_node {
    int ref;
    struct Object* elem;

    struct list_node* next;
};

#endif