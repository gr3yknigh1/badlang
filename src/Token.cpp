#include "badlang/Token.hpp"
#include "badlang/Macros.hpp"

std::string_view
TokenTypeToString(TokenType type) {
    switch (type) {
    case TOKEN_ID:
        return STRINGIFY(TOKEN_ID);
    case TOKEN_SEMI:
        return STRINGIFY(TOKEN_SEMI);
    case TOKEN_COLON:
        return STRINGIFY(TOKEN_COLON);
    case TOKEN_RARROW:
        return STRINGIFY(TOKEN_RARROW);
    case TOKEN_OP_ASSIGNMENT:
        return STRINGIFY(TOKEN_OP_ASSIGNMENT);
    case TOKEN_OP_COMPASSIGNMENT:
        return STRINGIFY(TOKEN_OP_COMPASSIGNMENT);
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
    case TOKEN_NOP:
        return STRINGIFY(TOKEN_NOP);
        break;
    }
    return "UNKNOWN";
}

Token::Token(const std::optional<std::string> &value, TokenType type)
    : Value(value), Type(type) {}