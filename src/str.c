
#include "badlang/str.h"

#include <stdlib.h>

#include <nostdlib/memory.h>
#include <nostdlib/types.h>

struct str
str_init(void) {
    return (struct str){
        .buf = nullptr,
        .len = 0,
    };
}

struct str
str_init_0(const char *str) {
    u64 len = str_len(str);
    char *buf = malloc(len * sizeof(char));
    noc_memory_copy(buf, str, len);

    return (struct str){
        .buf = buf,
        .len = len,
    };
}

struct str
str_init_1(const void *src, usize amount) {
    char *buf = malloc(amount * sizeof(char));
    noc_memory_copy(buf, src, amount);

    return (struct str){
        .buf = buf,
        .len = amount,
    };
}

void
str_concat(struct str *str, const char *other) {
    u64 other_len = str_len(other);
    u64 new_len = str->len + other_len;

    str->buf = realloc(str->buf, new_len);
    noc_memory_copy(str->buf + str->len, other, other_len);
    str->len = new_len;
}

void
str_free(struct str *str) {
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
