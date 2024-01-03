#ifndef BADLANG_TOKEN_HPP_
#define BADLANG_TOKEN_HPP_

#include <optional>
#include <string>
#include <string_view>

enum TokenType {
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
};

std::string_view TokenTypeToString(TokenType type);

struct Token {
    std::optional<std::string> Value;
    TokenType Type;

    Token(const std::optional<std::string> &value, TokenType type);
};

#endif // BADLANG_TOKEN_HPP_
