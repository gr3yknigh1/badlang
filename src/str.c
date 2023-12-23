#include "badlang/str.h"
#include <string.h>


struct str str_init(void) {
    return (struct str){
        .buffer = NULL,
        .len = 0,
    };
}

struct str
str_init_0(c_str_t s) {
    size_t len = c_str_len(s);
    char *buffer = malloc(len * sizeof(char));
    memcpy(buffer, s, len);

    return (struct str){
        .buffer = buffer,
        .len = len,
    };
}

struct str
str_init_1(const void *b, size_t len) {
    char *buffer = malloc(len * sizeof(char));
    memcpy(buffer, b, len);

    return (struct str){
        .buffer = buffer,
        .len = len,
    };
}

void str_concat_0(struct str *s, c_str_t other) {
    size_t other_len = c_str_len(other);
    size_t new_len = s->len + other_len;

    s->buffer = realloc(s->buffer, new_len);
    memcpy(s->buffer + s->len, other, other_len);
    s->len = new_len;
}

void str_free(struct str *s) {
    if (s->buffer != NULL) {
        free(s->buffer);
    }
}

size_t
c_str_len(c_str_t s) {
    size_t len = 0;
    while (*s++ != '\0') {
        len++;
    }
    return len;
}
