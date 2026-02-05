#include "mem.h"

#include "object.h"
#include "lists.h"
#include "structs.h"

void decr_ref(void *ptr, int type){
    switch (type) {
        case (LITERAL) : free(ptr); break;
        case (STRUCT) : decr_struct((struct_node*)ptr); break;
        case (LIST) : decr_dyn_list((list_node*)ptr); break;
        case (OBJECT) : decr_obj((object*)ptr); break;
    }
}

void incr_ref(void *ptr, int type){
    switch (type) {
        case (LITERAL) : break;
        case (STRUCT) : incr_struct((struct_node*)ptr); break;
        case (LIST) : incr_dyn_list((list_node*)ptr); break;
        case (OBJECT) : incr_obj((object*)ptr); break;
    }
}
