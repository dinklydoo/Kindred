#ifndef OBJECT_H
#define OBJECT_H

#include <stdlib.h>

typedef struct env_node {
    int env_id; // lookup for environment layout information
    void* payload; // payload as an allocation of one big block
} env_node;

typedef struct env_data {
    int type;
    size_t offset; // offset from payload base
    size_t size;
} env_data;

typedef struct env_layout {
    size_t payload_size;
    int var_count;
    env_data vars[];
} env_layout;

typedef struct closure {
    env_node* env;
    void* function_ptr;
    int ref;
} closure;

closure* allocate_closure(void* function_ptr, env_node* env);
void incr_closure(closure* c);
void decr_closure(closure* c);
env_node* get_env(closure* c);

env_node* allocate_env(int env_id);
void free_env(env_node* ptr);
void* access_var(env_node* ptr, int var_id);

#endif
