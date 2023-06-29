#ifndef H_STRING
#define H_STRING

size_t strlen(const char *str) {
    size_t ret = 0;
    while (*str++) {
        ret++;
    }
    return ret;
}

#endif