#include <stdint.h>

char char_bin_exp(char base, char exp){
    if (exp < 0) return 0;
    char res = 1;
    while (exp > 0) {
        if (exp & 1)
            res = res * base;
        base = base * base;
        exp >>= 1;
    }
    return res;
}

int32_t int_bin_exp(int32_t base, int32_t exp){
    if (exp < 0) return 0;
    int32_t res = 1;
    while (exp > 0) {
        if (exp & 1)
            res = res * base;
        base = base * base;
        exp >>= 1;
    }
    return res;
}

int64_t long_bin_exp(int64_t base, int64_t exp){
    if (exp < 0) return 0;
    int64_t res = 1;
    while (exp > 0) {
        if (exp & 1)
            res = res * base;
        base = base * base;
        exp >>= 1;
    }
    return res;
}