#ifndef BADLANG_RC_H_
#define BADLANG_RC_H_

enum rc {
    RC_END = -1,
    RC_OK = 0,
    RC_FAIL = 1,

    RC_FILE_NOT_FOUND,
    RC_FILE_FAIL_TO_OPEN,
};

#define IF_NOT_OK(__EXPR, __RCNAME)                                            \
    enum rc __RCNAME = RC_OK;                                                  \
    if ((__RCNAME = (__EXPR)) != RC_OK)

#endif // BADLANG_RC_H_