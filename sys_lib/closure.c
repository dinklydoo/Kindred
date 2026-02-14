#include "closure.h"
#include "mem.h"
#include "memory.h"

extern const env_layout CLOSURE_DATA[];

closure* allocate_closure(void* function_ptr, env_node* env){
    closure* c = (closure*)malloc(sizeof(closure));
    c->function_ptr = function_ptr;
    c->env = env;
    return c;
}

void free_closure(closure* c){
    decr_env(c->env);
    free(c);
}

env_node* allocate_env(int env_id){
    env_layout layout = CLOSURE_DATA[env_id];
    env_node* node = (env_node*)malloc(sizeof(env_node));
    node->env_id = env_id;
    node->ref = 1;
    node->payload = malloc(layout.payload_size);
    memset(node->payload, 0, layout.payload_size);

    return node;
}

void decr_env(env_node* ptr){
    ptr->ref--;
    if (ptr->ref == 0){
        // if struct is destroyed, decr all references to pointed objects
        env_layout layout = CLOSURE_DATA[ptr->env_id];

        for (int i = 0; i < layout.var_count; i++){
            env_data ed = layout.vars[i];

            char* payload_ptr = ((char*)ptr->payload) + ed.offset;
            if (ed.type != LITERAL) decr_ref(payload_ptr, ed.type);
        }
        free(ptr->payload); // free payload

        free(ptr); // free container
    }
};

void incr_env(env_node* ptr){
    ptr->ref++;
};

void* access_var(env_node* ptr, int var_id){
    env_layout layout = CLOSURE_DATA[ptr->env_id];
    env_data fd = layout.vars[var_id];

    char* payload_ptr = (char*)ptr->payload;
    payload_ptr += fd.offset;
    
    return (void*)payload_ptr;
}
