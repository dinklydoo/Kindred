#ifndef MEM_H
#define MEM_H

#define LITERAL 0
#define LIST 1
#define STRUCT 2
#define OBJECT 3

void* allocate_bool(bool);
void* allocate_char(char);
void* allocate_int(int);
void* allocate_long(long);
void* allocate_float(float);
void* allocate_double(double);

void decr_ref(void* ptr, int type);
void incr_ref(void* ptr, int type);

#endif