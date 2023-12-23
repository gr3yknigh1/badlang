#include "badlang/lexer.h"
#include "badlang/str.h"
#include "badlang/token.h"

#include <ctype.h>
#include <stdlib.h>

struct lexer
lexer_init(const char *source, size_t size) {
    return (struct lexer){
        .source = source,
        .curchar = *source,
        .pos = 0,
        .size = size,
    };
}

const char *lexer_peek(struct lexer *lexer, size_t offset) {
    size_t new_pos = lexer->pos + offset;

    if (new_pos >= lexer->size) {
        return lexer->source + lexer->size;
    }

    if (new_pos <= 0) {
        return lexer->source;
    }

    return lexer->source + offset;
}

void
lexer_parse(struct lexer *lexer, struct token *tokens) {
    struct token *curtoken = tokens;

    while (lexer->curchar != '\0') {
        lexer_skipwhitespace(lexer);

        if (isalpha(lexer->curchar)) {
            lexer_parse_id(lexer, curtoken);
            curtoken++;
            continue;
        }



        if (isdigit(lexer->curchar)) {
            lexer_parse_num(lexer, curtoken);
            curtoken++;
            continue;
        }

        lexer_advance(lexer);
    }

    *curtoken = token_init(str_init(), TOKEN_EOF);
}

void
lexer_parse_id(struct lexer *lexer, struct token *token) {

    const char *id_begin = lexer->source + lexer->pos;

    while (isalnum(lexer->curchar)) {
        lexer_advance(lexer);
    }

    const char *id_end = lexer->source + lexer->pos;

    *token = token_init(str_init_1(id_begin, id_end - id_begin), TOKEN_ID);
}

void
lexer_parse_num(struct lexer *lexer, struct token *token) {

    const char *id_begin = lexer->source + lexer->pos;

    while (isdigit(lexer->curchar)) {
        lexer_advance(lexer);
    }

    const char *id_end = lexer->source + lexer->pos;

    *token = token_init(str_init_1(id_begin, id_end - id_begin), TOKEN_LIT_NUM);
}


void
lexer_advance(struct lexer *lexer) {
    if (lexer->curchar == '\0') {
        return;
    }
    lexer->pos += 1;
    lexer->curchar = lexer->source[lexer->pos];
}

void
lexer_skipwhitespace(struct lexer *lexer) {
    while (isspace(lexer->curchar)) {
        lexer_advance(lexer);
    }
}
