#include "lists.h"
#include "object.h"
#include <stdlib.h>
#include <stdio.h>

// construct a new list
// assert : len > 0
struct list_node* allocate_dyn_list(size_t elem, int len){
    struct list_node* head = malloc(sizeof(struct list_node));
    head->ref = 1;
    struct list_node* curr = head;
    for (int i = 1; i < len; i++){
        struct list_node* temp = malloc(sizeof(struct list_node));
        temp->ref = 1;
        temp->elem = NULL;
        temp->next = NULL;

        curr->next = temp;
        curr = temp;
    }
    return head;
}

struct list_node* index_dyn_node(struct list_node* head, int index){
    if (head == NULL){
        fprintf(stderr, "Error: List index %d out of bounds", index);
        exit(1);
    }
    struct list_node* curr = head;
    for (int i = 0; i < index; i++){
        if (!curr->next){
            fprintf(stderr, "Error: List index %d out of bounds", index);
            exit(1);
        }
        curr = curr->next;
    }
    return curr;
}

struct Object* index_dyn_list(struct list_node* head, int index){
    struct list_node* temp = index_dyn_node(head, index);
    return temp->elem;
}

void decr_dyn_index(struct list_node* head, int index){
    struct list_node* curr = head;
    curr->ref--;
    if (curr->ref == 0){

        if (index > 0){
            struct list_node* prev = index_dyn_node(head, index-1);
            prev->next = curr->next;
        }
        decr_ref(curr->elem);
        free(curr);
    }
}

void decr_dyn_list(struct list_node* head){
    struct list_node* prev = NULL;
    struct list_node* curr = head;
    while (curr){
        curr->ref--;
        if (curr->ref == 0){
            if (prev) prev->next = curr->next;
            struct list_node* temp = curr;
            curr = curr->next;

            decr_ref(temp->elem);
            free(temp);
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
}


void incr_dyn_list(struct list_node* head){
    struct list_node* curr = head;
    while (curr){
        curr->ref++;
        curr = curr->next;
    }
}

struct list_node* copy_dyn_list(struct list_node* src){
    if (!src) return NULL;

    struct list_node* curr = src;

    struct list_node* head = NULL;
    struct list_node* prev = NULL;
    while (curr){
        struct list_node* temp = malloc(sizeof(struct list_node));
        if (!head) head = temp;

        temp->elem = curr->elem;
        temp->ref = 1;
        temp->next = NULL;
        
        if (prev) prev->next = temp;
        prev = temp;
    }
    return head;
}

struct list_node* dyn_list_concat(struct list_node* head, struct list_node* tail){
    if (!head) return copy_dyn_list(tail);

    struct list_node* h_copy = copy_dyn_list(head);
    struct list_node* curr = h_copy;
    while (curr->next) curr = curr->next;
    curr->next = tail;

    incr_dyn_list(tail);
    return h_copy;
}

// static list for later optimizations

// struct Object* allocate_stc_list(size_t elem, int len){
//     struct Object* container = allocate_obj(elem * len);
//     return container;
// }




