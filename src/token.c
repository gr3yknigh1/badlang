#include "badlang/token.h"


const char *token_type_to_str(int token_type) {
    switch(token_type) {
    case TOKEN_ID:
        return "TOKEN_ID";
    case TOKEN_SEMI:
        return "TOKEN_SEMI";
    case TOKEN_COLON:
        return "TOKEN_COLON";
    case TOKEN_RARROW:
        return "TOKEN_RARROW";
    case TOKEN_OP_COMPEQ:
        return "TOKEN_OP_COMPEQ";
    case TOKEN_OP_COMPTIME:
        return "TOKEN_OP_COMPTIME";
    case TOKEN_LPAREN:
        return "TOKEN_LPAREN";
    case TOKEN_RPAREN:
        return "TOKEN_RPAREN";
    case TOKEN_LCURLY:
        return "TOKEN_LCURLY";
    case TOKEN_RCURLY:
        return "TOKEN_RCURLY";
    }
    return "UNKNOWN";
}
