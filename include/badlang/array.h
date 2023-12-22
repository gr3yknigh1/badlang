/*
 * Static array library
 * */
#ifndef BADLANG_ARRAY_H_
#define BADLANG_ARRAY_H_

#define ARRAY(__NAME, __SIZE, __TYPE)                                          \
    struct {                                                                   \
        __TYPE _items[(__SIZE)];                                               \
        unsigned long _length;                                                      \
    } __NAME

#define ARRAY_ADD(__ARRAY, __ITEM)                                             \
    (__ARRAY)._items[(__ARRAY)._length++] = __ITEM

#define ARRAY_LEN(__ARRAY) ((__ARRAY)._length)

#define ARRAY_GET(__ARRAY, __IDX) ((__ARRAY)._items[(__IDX)])

#define ARRAY_FOR(__ARRAY, __IDX)                                              \
    for (unsigned long __IDX = 0; __IDX < ARRAY_LEN(__ARRAY); ++__IDX)

#endif // BADLANG_ARRAY_H_
