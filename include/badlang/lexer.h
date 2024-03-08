#ifndef BADLANG_LEXER_H_
#define BADLANG_LEXER_H_

#include "badlang/token.h"

#include <nostdlib/types.h>

struct lexer {
    const char *source;
    char curchar;
    unsigned long long pos;
    unsigned long long size;
};

struct lexer lexer_init(const char *source, usize size);

const char *lexer_peek(const struct lexer *lexer, usize offset);

bool lexer_is_source_end(const struct lexer *lexer);

u64 lexer_parse(struct lexer *lexer, struct token *tokens);

struct token lexer_parse_id(struct lexer *lexer);
struct token lexer_parse_num(struct lexer *lexer);

void lexer_advance(struct lexer *lexer);
void lexer_skipwhitespace(struct lexer *lexer);

#endif // BADLANG_LEXER_H_
