#include "badlang/lexer.h"
#include "badlang/token.h"

#include <ctype.h>

struct lexer
lexer_init(const char *source, usize size) {
    return (struct lexer){
        .source = source,
        .curchar = *source,
        .pos = 0,
        .size = size,
    };
}

const char *
lexer_peek(const struct lexer *lexer, usize offset) {
    usize new_pos = lexer->pos + offset;

    if (new_pos >= lexer->size) {
        return lexer->source + lexer->size;
    }

    if (new_pos <= 0) {
        return lexer->source;
    }

    return lexer->source + offset;
}

bool
lexer_is_source_end(const struct lexer *lexer) {
    return lexer->curchar == '\0';
}

u64
lexer_parse(struct lexer *lexer, struct Token *tokens) {
    struct Token *curtoken = tokens;

    while (!lexer_is_source_end(lexer)) {
        lexer_skipwhitespace(lexer);

        if (isalpha(lexer->curchar)) {
            *curtoken++ = lexer_parse_id(lexer);
            continue;
        }

        if (isdigit(lexer->curchar)) {
            *curtoken++ = lexer_parse_num(lexer);
            continue;
        }

        switch (lexer->curchar) {
        case ':':
            if (lexer->source[lexer->pos + 1] == ':') {
                *curtoken++ =
                    token_init(str_init_0("::"), TOKEN_OP_COMPASSIGNMENT);
                lexer_advance(lexer);
            } else {
                *curtoken++ = token_init(str_init_0(":"), TOKEN_COLON);
            }
            break;
        case '=':
            *curtoken++ = token_init(str_init_0("="), TOKEN_OP_ASSIGNMENT);
            break;
        case '(':
            *curtoken++ = token_init(str_init_0("("), TOKEN_LPAREN);
            break;
        case ')':
            *curtoken++ = token_init(str_init_0(")"), TOKEN_RPAREN);
            break;
        case '-':
            if (lexer->source[lexer->pos + 1] == '>') {
                *curtoken++ = token_init(str_init_0("->"), TOKEN_RARROW);
                lexer_advance(lexer);
            }
            break;
        case '{':
            *curtoken++ = token_init(str_init_0("{"), TOKEN_LCURLY);
            break;
        case '}':
            *curtoken++ = token_init(str_init_0("}"), TOKEN_RCURLY);
            break;
        case ';':
            *curtoken++ = token_init(str_init_0(";"), TOKEN_SEMI);
            break;
        }

        lexer_advance(lexer);
    }

    *curtoken = token_init(str_init(), TOKEN_EOF);
    return curtoken - tokens;
}

struct Token
lexer_parse_id(struct lexer *lexer) {

    const char *id_begin = lexer->source + lexer->pos;

    while (isalnum(lexer->curchar)) {
        lexer_advance(lexer);
    }

    const char *id_end = lexer->source + lexer->pos;

    return token_init(str_init_1(id_begin, id_end - id_begin), TOKEN_ID);
}

struct Token
lexer_parse_num(struct lexer *lexer) {

    const char *id_begin = lexer->source + lexer->pos;

    while (isdigit(lexer->curchar)) {
        lexer_advance(lexer);
    }

    const char *id_end = lexer->source + lexer->pos;

    return token_init(str_init_1(id_begin, id_end - id_begin), TOKEN_LIT_NUM);
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
