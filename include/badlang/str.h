#ifndef BADLANG_STR_H_
#define BADLANG_STR_H_

#include <nostdlib/types.h>

typedef struct {
    char *buf;
    u64 len;
} str_t;

str_t str_init(void);
str_t str_init_0(const char *str);
str_t str_init_1(const void *src, usize amount);

void str_concat(str_t *str, const char *other);

void str_free(str_t *str);

u64 str_len(const char *str);

#endif // BADLANG_STR_H_
