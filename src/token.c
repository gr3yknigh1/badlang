#include "badlang/token.h"
#include "badlang/marcos.h"


struct token token_init(struct str value, enum token_type type) {
    return (struct token) {
        .value = value,
        .type = type,
    };
}

const char *
token_type_to_str(int token_type) {
    switch (token_type) {
    case TOKEN_ID:
        return STRINGIFY(TOKEN_ID);
    case TOKEN_SEMI:
        return STRINGIFY(TOKEN_SEMI);
    case TOKEN_COLON:
        return STRINGIFY(TOKEN_COLON);
    case TOKEN_RARROW:
        return STRINGIFY(TOKEN_RARROW);
    case TOKEN_OP_COMPEQ:
        return STRINGIFY(TOKEN_OP_COMPEQ);
    case TOKEN_OP_COMPTIME:
        return STRINGIFY(TOKEN_OP_COMPTIME);
    case TOKEN_LPAREN:
        return STRINGIFY(TOKEN_LPAREN);
    case TOKEN_RPAREN:
        return STRINGIFY(TOKEN_RPAREN);
    case TOKEN_LCURLY:
        return STRINGIFY(TOKEN_LCURLY);
    case TOKEN_RCURLY:
        return STRINGIFY(TOKEN_RCURLY);
    case TOKEN_LIT_NUM:
        return STRINGIFY(TOKEN_LIT_NUM);
    case TOKEN_LIT_STR:
        return STRINGIFY(TOKEN_LIT_STR);
    case TOKEN_EOF:
        return STRINGIFY(TOKEN_EOF);
    }
    return "UNKNOWN";
}
