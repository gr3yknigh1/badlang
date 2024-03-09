
#include "badlang/str.h"

#include <stdlib.h>

#include <nostdlib/memory.h>
#include <nostdlib/types.h>

str_t
str_init(void) {
    return (str_t){
        .buf = nullptr,
        .len = 0,
    };
}

str_t
str_init_0(const char *str) {
    u64 len = str_len(str);
    char *buf = malloc(len * sizeof(char));
    noc_memory_copy(buf, str, len);

    return (str_t){
        .buf = buf,
        .len = len,
    };
}

str_t
str_init_1(const void *src, usize amount) {
    char *buf = malloc(amount * sizeof(char));
    noc_memory_copy(buf, src, amount);

    return (str_t){
        .buf = buf,
        .len = amount,
    };
}

void
str_concat(str_t *str, const char *other) {
    u64 other_len = str_len(other);
    u64 new_len = str->len + other_len;

    str->buf = realloc(str->buf, new_len);
    noc_memory_copy(str->buf + str->len, other, other_len);
    str->len = new_len;
}

void
str_free(str_t *str) {
    if (str->buf != nullptr) {
        free(str->buf);
    }
}

u64
str_len(const char *s) {
    u64 len = 0;
    while (*s++ != '\0') {
        len++;
    }
    return len;
}
