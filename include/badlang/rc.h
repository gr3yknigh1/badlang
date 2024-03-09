#ifndef BADLANG_RC_H_
#define BADLANG_RC_H_

typedef enum {
    RC_END = -1,
    RC_OK = 0,
    RC_ERR = 1,

    RC_FILE_NOT_FOUND,
    RC_FILE_FAIL_TO_OPEN,
} rc_t;

#define IF_NOT_OK(__EXPR, __RCNAME)                                            \
    rc_t __RCNAME = RC_OK;                                                     \
    if ((__RCNAME = (__EXPR)) != RC_OK)

#endif // BADLANG_RC_H_
