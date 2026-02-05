#include "structs.h"
#include "mem.h"

extern const struct_layout STRUCT_DATA[];

struct_node* allocate_struct(int struct_id){
    struct_layout layout = STRUCT_DATA[struct_id];
    struct_node* node = (struct_node*)malloc(sizeof(struct_node));
    node->struct_id = struct_id;
    node->ref = 1;
    node->payload = malloc(layout.payload_size);

    return node;
}

void decr_struct(struct_node* ptr){
    ptr->ref--;
    if (ptr->ref == 0){
        // if struct is destroyed, decr all references to pointed objects
        struct_layout layout = STRUCT_DATA[ptr->struct_id];

        for (int i = 0; i < layout.field_count; i++){
            field_data fd = layout.fields[i];

            char* payload_ptr = ((char*)ptr->payload) + fd.offset;
            if (fd.type != LITERAL) decr_ref(payload_ptr, fd.type);
        }
        free(ptr->payload); // free payload

        free(ptr); // free container
    }
};

void incr_struct(struct_node* ptr){
    ptr->ref++;
};

void* access_field(struct_node* ptr, int field_id){
    struct_layout layout = STRUCT_DATA[ptr->struct_id];
    field_data fd = layout.fields[field_id];

    char* payload_ptr = (char*)ptr->payload;
    payload_ptr += fd.offset;
    
    return (void*)payload_ptr;
}