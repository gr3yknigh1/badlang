#ifndef BADLANG_TOKEN_H_
#define BADLANG_TOKEN_H_

#include "badlang/str.h"

enum token_type {
    TOKEN_NOP,
    TOKEN_ID,

    TOKEN_SEMI,
    TOKEN_COLON,

    TOKEN_RARROW,

    TOKEN_OP_COMPEQ,
    TOKEN_OP_COMPTIME,

    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LCURLY,
    TOKEN_RCURLY,

    TOKEN_LIT_NUM,
    TOKEN_LIT_STR,

    TOKEN_EOF,
};

struct token {
    enum token_type type;
    struct str value;
};

struct token token_init(struct str value, enum token_type type);

const char *token_type_to_str(int token_type);

#endif // BADLANG_TOKEN_H_
