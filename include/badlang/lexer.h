#ifndef BADLANG_LEXER_H_
#define BADLANG_LEXER_H_

#include "badlang/token.h"

struct lexer {
    const char *source;
    char curchar;
    unsigned long long pos;
    unsigned long long size;
};

struct lexer lexer_init(const char *source, size_t size);

const char *lexer_peek(struct lexer *lexer, size_t offset);

void lexer_parse(struct lexer *lexer, struct token *tokens);
void lexer_parse_id(struct lexer *lexer, struct token *token);
void lexer_parse_num(struct lexer *lexer, struct token *token);

void lexer_advance(struct lexer *lexer);
void lexer_skipwhitespace(struct lexer *lexer);

#endif // BADLANG_LEXER_H_
