#ifndef BADLANG_STR_H_
#define BADLANG_STR_H_

#include "badlang/types.h"

struct str {
    char *buf;
    u64 len;
};

struct str str_init(void);
struct str str_init_0(const char *str);
struct str str_init_1(const void *src, usize amount);

void str_concat(struct str *str, const char *other);

void str_free(struct str *str);

u64 str_len(const char *str);

#endif // BADLANG_STR_H_
