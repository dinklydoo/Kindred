#include "lists.h"

#include "mem.h"

list_node* cons(void* elem, int type, list_node* tail){
    list_node* n = (list_node*)malloc(sizeof(list_node));
    n->ref = 1;
    n->elem = elem;
    n->type = type;
    n->next = tail;

    incr_ref(elem, type);
    if (tail) tail->ref++;

    return n;
}

void decr_dyn_list(list_node* n){
    if (!n) return;

    if (--n->ref > 0)
        return;

    decr_ref(n->elem, n->type);
    decr_dyn_list(n->next);
    free(n);
}

void incr_dyn_list(list_node* n){
    if (!n) return;
    n->ref++;
    incr_dyn_list(n->next);
}

list_node* remove_at(list_node* list, int index){
    if (!list) abort();
    if (index == 0)
        return list->next;  // share tail

    return cons(
        list->elem,
        list->type,
        remove_at(list->next, index - 1)
    );
}

list_node* append(list_node* list, void* elem, int type){
    if (!list)
        return cons(elem, type, NULL);

    return cons(
        list->elem,
        list->type,
        append(list->next, elem, type)
    );
}

list_node* concat(list_node* a, list_node* b){
    if (!a) {
        if (b) b->ref++;
        return b;
    }

    return cons(
        a->elem,
        a->type,
        concat(a->next, b)
    );
}