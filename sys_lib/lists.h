#ifndef LISTS_H
#define LISTS_H

#include <stdlib.h>

typedef struct list_node {
    int ref;
    int type;
    size_t elem_size;
    void* elem = NULL;
    struct list_node* next = NULL;
} list_node;

list_node* alloc_list(int type, size_t size, int length);
list_node* cons(int type, size_t size, list_node* tail);
list_node* access_node(list_node* list, int index);
void* index_list(list_node* list, int index);
void decr_list(list_node* n);
void incr_list(list_node* n);
list_node* remove_at(list_node* list, int index);
list_node* concat(list_node* a, list_node* b);
int list_size(list_node* list);
bool list_equals(list_node* a, list_node* b);

list_node* construct_string(char* str);

#endif