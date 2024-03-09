#ifndef BADLANG_TOKEN_H_
#define BADLANG_TOKEN_H_

#include "badlang/str.h"

typedef enum {
    TOKEN_NOP,
    TOKEN_ID,

    TOKEN_SEMI,
    TOKEN_COLON,

    TOKEN_RARROW,

    TOKEN_OP_ASSIGNMENT,

    TOKEN_OP_COMPASSIGNMENT,
    TOKEN_OP_COMPTIME,

    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LCURLY,
    TOKEN_RCURLY,

    TOKEN_LIT_NUM,
    TOKEN_LIT_STR,

    TOKEN_EOF,
} token_type_t;

typedef struct {
    token_type_t type;
    str_t value;
} token_t;

token_t token_init(str_t value, token_type_t type);

void token_free(token_t *t);

const char *token_type_to_str(int token_type);

#endif // BADLANG_TOKEN_H_
