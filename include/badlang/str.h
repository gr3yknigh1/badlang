#ifndef BADLANG_STR_H_
#define BADLANG_STR_H_

#include <stdlib.h>

#define OWN_HEAP

typedef const char *c_str_t;

struct str {
    char *buffer;
    size_t len;
};

struct str str_init(void);
struct str str_init_0(c_str_t s);
struct str str_init_1(const void *buffer, size_t size);

void str_concat(struct str *s, struct str *other);
void str_concat_0(struct str *s, c_str_t other);

void str_free(struct str *s);

size_t c_str_len(c_str_t s);

#endif // BADLANG_STR_H_
