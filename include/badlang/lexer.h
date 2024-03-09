#ifndef BADLANG_LEXER_H_
#define BADLANG_LEXER_H_

#include "badlang/token.h"

#include <nostdlib/types.h>

typedef struct {
    const char *source;
    char curchar;
    unsigned long long pos;
    unsigned long long size;
} lexer_t;

lexer_t lexer_init(const char *source, usize size);

const char *lexer_peek(const lexer_t *lexer, usize offset);

bool lexer_is_source_end(const lexer_t *lexer);

u64 lexer_parse(lexer_t *lexer, token_t *tokens);

token_t lexer_parse_id(lexer_t *lexer);
token_t lexer_parse_num(lexer_t *lexer);

void lexer_advance(lexer_t *lexer);
void lexer_skipwhitespace(lexer_t *lexer);

#endif // BADLANG_LEXER_H_
