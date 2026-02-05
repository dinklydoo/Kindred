#ifndef LISTS_H
#define LISTS_H

#include <stdlib.h>

typedef struct list_node {
    int ref;
    int type;
    void* elem = NULL;
    struct list_node* next = NULL;
} list_node;

list_node* cons(void* elem, int type, list_node* tail);
void decr_dyn_list(list_node* n);
void incr_dyn_list(list_node* n);
list_node* remove_at(list_node* list, int index);
list_node* append(list_node* list, void* elem, int type);
list_node* concat(list_node* a, list_node* b);

#endif