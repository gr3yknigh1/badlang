#ifndef BADLANG_TOKEN_H_
#define BADLANG_TOKEN_H_

struct token {
    enum {
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
    } type;

    char *value;
};

const char *token_type_to_str(int token_type);

#endif // BADLANG_TOKEN_H_
