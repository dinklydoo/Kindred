#include <stdlib.h>
#include <stdbool.h>
#include "lists.h"

bool read_bool();
char read_char();
int32_t read_int();
int64_t read_long();
float read_float();
double read_double();

void print_bool(bool);
void print_char(char);
void print_int(int32_t);
void print_long(int64_t);
void print_float(float);
void print_double(double);
void print_string(list_node* ptr);
// void print_list(list_node* ptr);
// void print_struct(struct_node* ptr);
