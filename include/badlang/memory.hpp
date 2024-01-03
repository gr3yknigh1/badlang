#ifndef BADLANG_MEMORY_H_
#define BADLANG_MEMORY_H_

#include <stdlib.h>

#include "badlang/types.h"

#define memory_allocate malloc
#define memory_reallocate realloc

void memory_copy(void *restrict dst, const void *src, usize amount);

void free_if_not_null(void *p);

#endif // BADLANG_MEMORY_H_
