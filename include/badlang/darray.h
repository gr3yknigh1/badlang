#ifndef BADLANG_DARRAY_H_
#define BADLANG_DARRAY_H_

#include <nostdlib/types.h>

typedef struct {
    void *items;
    usize item_size;
    u64 item_count;
    u64 item_capacity;
} darray_t;

#define DARRAY_FREE_SPACE_BEGIN(__DARRAY_PTR)                                  \
    ((__DARRAY_PTR)->item_count * (__DARRAY_PTR)->item_size)
#define DARRAY_BUFFER_CAPACITY_BYTES(__DARRAY_PTR)                             \
    ((__DARRAY_PTR)->item_capacity * (__DARRAY_PTR)->item_size)
#define DARRAY_FOREACH(__DARRAY_PTR, __TYPE, __IT)                             \
    for (__TYPE *__IT = (__DARRAY_PTR)->items;                                 \
         __IT !=                                                               \
         ((__TYPE *)(__DARRAY_PTR)->items) + (__DARRAY_PTR)->item_count;       \
         __IT++)

/*
 * Dynamic array initalization function
 */
void darray_init(darray_t *out_darray, u64 item_capacity, usize item_size);

/*
 * Copies item and pushes it at the and of buffer
 */
void darray_push(darray_t *darray, void *item);

/*
 * Just moving pointer of buffer end to the left by `item_size`. And copies to
 * the `out_item` ptr last item value
 */
void darray_pop(darray_t *darray, void *out_item);

/*
 * Assigning `out_ptr_item` to value of last item address
 */
void darray_peek(const darray_t *darray, void const **const out_ptr_item);

/*
 * Deallocates inner buffer and setting all stats except `item_size` to zero
 */
void darray_free(darray_t *darray);

#endif // BADLANG_DARRAY_H_
