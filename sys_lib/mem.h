#ifndef MEM_H
#define MEM_H

#define LITERAL 0
#define LIST 1
#define STRUCT 2
#define CLOSURE 3

void decr_ref(void* ptr, int type);
void incr_ref(void* ptr, int type);

#endif