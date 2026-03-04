#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

typedef struct struct_node {
    int ref;
    int struct_id; // lookup for struct layout information
    void* payload; // payload as an allocation of one big block
} struct_node;

typedef struct field_data {
    int type;
    size_t offset; // offset from payload base
    size_t size;
} field_data;

typedef struct struct_layout {
    size_t payload_size;
    int field_count;
    field_data fields[10]; // FIX THIS
} struct_layout;

struct_node* allocate_struct(int struct_id);
void decr_struct(struct_node* ptr);
void incr_struct(struct_node* ptr);

void* access_field(struct_node* ptr, int field_id);
bool struct_equals(struct_node* a, struct_node* b);

#endif
