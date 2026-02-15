#include "mem.h"

#include "closure.h"
#include "lists.h"
#include "structs.h"

void decr_ref(void *ptr, int type){
    switch (type) {
        case (LITERAL) : free(ptr); break;
        case (STRUCT) : decr_struct((struct_node*)ptr); break;
        case (LIST) : decr_list((list_node*)ptr); break;
        case (CLOSURE) : decr_closure((closure*)ptr); break;
    }
}

void incr_ref(void *ptr, int type){
    switch (type) {
        case (LITERAL) : break;
        case (STRUCT) : incr_struct((struct_node*)ptr); break;
        case (LIST) : incr_list((list_node*)ptr); break;
        case (CLOSURE) : incr_closure((closure*)ptr); break;
    }
}
