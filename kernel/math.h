#ifndef H_MATH
#define H_MATH

#include <stdint.h>

int16_t abs(int16_t num) {
    int sign = num >= 0 ? 1 : -1;
    return num * sign;
}

#endif