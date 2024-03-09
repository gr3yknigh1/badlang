/*
 * Static array library
 * */
#ifndef BADLANG_ARRAY_H_
#define BADLANG_ARRAY_H_

#define ARRAY(__TYPE, __SIZE)                                                  \
    struct {                                                                   \
        __TYPE items[(__SIZE)];                                                \
        unsigned long length;                                                  \
    }

#define ARRAY_ADD(__ARRAY, __ITEM) (__ARRAY).items[(__ARRAY).length++] = __ITEM

#define ARRAY_LEN(__ARRAY) ((__ARRAY).length)

#define ARRAY_GET(__ARRAY, __IDX) ((__ARRAY).items[(__IDX)])

#define ARRAY_FOR(__ARRAY, __IDX)                                              \
    for (unsigned long __IDX = 0; __IDX < ARRAY_LEN(__ARRAY); ++__IDX)

#endif // BADLANG_ARRAY_H_
