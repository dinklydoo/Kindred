#include "lists.h"

#include "mem.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>

list_node* alloc_list(int type, size_t size, int length){
    if (length == 0) return NULL;

    list_node* head = cons(type, size, NULL);
    list_node* curr = head;
    for (int i = 1; i < length; i++){
        list_node* temp = cons(type, size, NULL);
        curr->next= temp;
        curr = temp;
    }
    return head;
}

list_node* cons(int type, size_t size, list_node* tail){
    list_node* n = (list_node*)malloc(sizeof(list_node));
    n->ref = 1;
    n->type = type;
    n->elem_size = size;
    n->elem = malloc(size);
    n->next = tail;

    return n;
}

list_node* access_node(list_node* list, int index){
    list_node* temp = list;
    while (index > 0){
        if (!temp){
            fprintf(stderr, "Runtime Error: list index %d out of bounds\n", index);
            exit(1);
        }
        temp = temp->next;
        index--;
    }
    return temp;
}

void* index_list(list_node* list, int index){
    list_node* temp = list;
    while (index > 0){
        if (!temp){
            fprintf(stderr, "Runtime Error: list index %d out of bounds\n", index);
            exit(1);
        }
        temp = temp->next;
        index--;
    }
    if (!temp){
        fprintf(stderr, "Runtime Error: list index %d on an empty list\n", index);
        exit(1);
    }
    return temp->elem;
}

void decr_list(list_node* n){
    if (!n) return;

    if (--n->ref > 0)
        return;

    decr_ref(n->elem, n->type);
    decr_list(n->next);
    free(n);
}

void incr_list(list_node* n){
    if (!n) return;
    n->ref++;
}

list_node* remove_at(list_node* list, int index){
    if (!list) abort();
    if (index == 0)
        return list->next;  // share tail

    return cons(
        list->type,
        list->elem_size,
        remove_at(list->next, index - 1)
    );
}

list_node* concat_list(list_node* a, list_node* b){
    if (!a) return b;

    list_node* a_copy = cons(
        a->type, a->elem_size,
        concat_list(a->next, b)
    );

    memcpy(a_copy->elem, a->elem, a->elem_size);
    return a_copy;
}

int list_size(list_node* a){
    list_node* curr = a;
    int size = 0;
    while (curr){
        size++;
        curr = curr->next;
    }
    return size;
}

bool list_equals(list_node* a, list_node* b){
    if (a == b) return true;

    list_node* ap = a;
    list_node* bp = b;

    while (true) {
        if (ap == bp) return true;
        if (!ap || !bp) return false;
        
        if (ap->type == LITERAL){
            unsigned char* a_elem = (unsigned char*)ap->elem;
            unsigned char* b_elem = (unsigned char*)bp->elem;
            for (int i = 0; i < ap->elem_size; i++){
                if (*a_elem != *b_elem) return false;
                a_elem++; b_elem++;
            }
        }
        else if (ap->type == STRUCT){ if (!struct_equals((struct_node*)ap->elem, (struct_node*)bp->elem)) return false; }
        else { if (!list_equals((list_node*)ap->elem, (list_node*)bp->elem)) return false; }

        ap = ap->next; bp = bp->next;
    }
    return true;
}

list_node* construct_string(char* str){
    if (!str || *str == '\0') return NULL;
    list_node* head = cons(LITERAL, sizeof(char), NULL);
    *(char*)head->elem = str[0];
    list_node* curr = head;

    for (int i = 1; str[i] != '\0'; i++){
        list_node* temp = cons(LITERAL, sizeof(char), NULL);
        *(char*)temp->elem = str[i];
        curr->next = temp;
        curr = temp;
    }
    return head;
}