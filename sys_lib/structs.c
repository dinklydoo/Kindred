#include "structs.h"
#include "mem.h"
#include "lists.h"
#include <stdio.h>

extern const struct_layout STRUCT_DATA[];

struct_node* allocate_struct(int struct_id){
    struct_layout layout = STRUCT_DATA[struct_id];
    struct_node* node = (struct_node*)malloc(sizeof(struct_node));
    node->struct_id = struct_id;
    node->ref = 1;
    node->payload = malloc(layout.payload_size);
    if (!node->payload){
        fprintf(stderr,"Struct Allocation failed\n");
        exit(1);
    }
    memset(node->payload, 0, layout.payload_size);

    return node;
}

void decr_struct(struct_node* ptr){
    if (ptr == NULL) return;
    ptr->ref--;
    if (ptr->ref == 0){
        // if struct is destroyed, decr all references to pointed objects
        struct_layout layout = STRUCT_DATA[ptr->struct_id];

        for (int i = 0; i < layout.field_count; i++){
            field_data fd = layout.fields[i];

            char* payload_ptr = ((char*)ptr->payload) + fd.offset;
            if (fd.type != LITERAL) decr_ref(*(void**)payload_ptr, fd.type);
        }
        free(ptr->payload); // free payload

        free(ptr); // free container
    }
};

void incr_struct(struct_node* ptr){
    if (ptr == NULL) return;
    ptr->ref++;
};

void* access_field(struct_node* ptr, int field_id){
    if (ptr == NULL){
        fprintf(stderr,"Runtime Error: Field access on nil value\n");
        exit(1);
    }
    struct_layout layout = STRUCT_DATA[ptr->struct_id];
    field_data fd = layout.fields[field_id];

    char* payload_ptr = (char*)ptr->payload;
    payload_ptr += fd.offset;
    
    return (void*)payload_ptr;
}

bool struct_equals(struct_node *a, struct_node *b){
    if (a==b) return true;

    // null compare to non-null
    if (a==NULL || b==NULL) return false;
    
    struct_layout layout = STRUCT_DATA[a->struct_id];

    for (int i = 0; i < layout.field_count; i++){
        field_data fd = layout.fields[i];
        void* a_field = (char*)a->payload + fd.offset;
        void* b_field = (char*)b->payload + fd.offset;

        if (fd.type == LITERAL){
            if (memcmp(a_field, b_field, fd.size) != 0)
                return false;
        }
        else if (fd.type == STRUCT){ if (!struct_equals(*(struct_node**)a_field, *(struct_node**)b_field)) return false; }
        else { if (!list_equals(*(list_node**)a_field, *(list_node**)b_field)) return false; }
    }
    return true;
}