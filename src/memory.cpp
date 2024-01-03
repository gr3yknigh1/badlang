#include "badlang/memory.h"

#include <stdlib.h>

void
memory_copy(void *restrict dst, const void *src, usize amount) {
    while (amount-- > 0) {
        ((char *)dst)[amount] = ((char *)src)[amount];
    }
}

void
free_if_not_null(void *p) {
    if (p == null) {
        return;
    }
    free(p);
}
