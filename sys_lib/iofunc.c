#include "iofunc.h"
#include <stdio.h>

bool read_bool(){
    int temp;
    if (scanf("%d", &temp) == 0) return false;
    return true;
}
char read_char(){
    char temp;
    scanf("%c", &temp);
    return temp;
}
int32_t read_int(){
    int32_t temp;
    scanf("%d", &temp);
    return temp;
}
int64_t read_long(){
    int64_t temp;
    scanf("%lld", &temp);
    return temp;
}
float read_float(){
    float temp;
    scanf("%f", &temp);
    return temp;
}
double read_double(){
    double temp;
    scanf("%lf", &temp);
    return temp;
}
list_node* read_string(){
    char buf[1024];
    scanf("%s", buf);
    return construct_string(buf);
}

void print_bool(bool val){
    if (val == true) printf("TRUE");
    else printf("FALSE");
}

void print_char(char val){
    printf("%c", val);
}

void print_int(int32_t val){
    printf("%d", val);
}
void print_long(int64_t val){
    printf("%lld", val);
}
void print_float(float val){
    printf("%f", val);
}
void print_double(double val){
    printf("%lf", val);
}

void print_string(list_node* ptr){
    while (ptr) {
        print_char(*((char*)ptr->elem));
        ptr = ptr->next;
    }
}

// void print_struct(struct_node* ptr){

// }