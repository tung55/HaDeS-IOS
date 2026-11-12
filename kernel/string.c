#include "string.h"

void* memset(void* dest, int val, size_t len) {
    unsigned char* ptr = dest;
    while (len-- > 0) *ptr++ = val;
    return dest;
}
void* memcpy(void* dest, const void* src, size_t len) {
    char* d = dest; const char* s = src;
    while (len--) *d++ = *s++;
    return dest;
}
size_t strlen(const char* str) {
    size_t len = 0; while (str[len]) len++;
    return len;
}
