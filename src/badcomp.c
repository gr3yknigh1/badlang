/*
 * BADCOMP
 *
 * */
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "badlang/array.h"
#include "badlang/bits.h"
#include "badlang/fs.h"
#include "badlang/lexer.h"
#include "badlang/logs.h"
#include "badlang/rc.h"

#define SOURCES_MAX_COUNT 32
#define TOKENS_MAX_COUNT 1024

enum opt {
    OPT_NONE = MKFLAG(0),
    OPT_HELP = MKFLAG(1),
};

static const struct option LONG_OPTS[] = {
    {"help", false, NULL, OPT_HELP},
};

static const char *SHORT_OPTS = "h";

static enum rc
badlang_compile(const char *source, size_t size) {
    struct lexer lexer = lexer_init(source, size);
    struct token *tokens = calloc(TOKENS_MAX_COUNT, sizeof(struct token));
    lexer_parse(&lexer, tokens);

    struct token *token = tokens;

    char *token_value = NULL;

    while (token->type != TOKEN_EOF) {

        token_value = realloc(token_value, token->value.len + 1);
        memcpy(token_value, token->value.buffer, token->value.len);
        token_value[token->value.len] = '\0';

        printf("Token(value=[%s] type=%s)\n", token_value,
               token_type_to_str(token->type));
        token++;
    }

    return RC_OK;
}

static enum rc
badlang_compile_file(const char *source_file) {
    if (!fs_exists(source_file)) {
        return RC_FILE_NOT_FOUND;
    }

    FILE *f = fopen(source_file, "r");

    if (f == NULL) {
        return RC_FILE_FAIL_TO_OPEN;
    }

    size_t file_size = fs_file_size(f);
    char *file_content = malloc(file_size * sizeof(char));
    fread(file_content, file_size, 1, f);

    enum rc rc = badlang_compile(file_content, file_size);

    free(file_content);

    return rc;
}

int
main(int argc, char *const *argv) {
    int opt_value = 0, opt_index = 0;
    enum opt optmask = OPT_NONE;

    while ((opt_value = getopt_long(argc, argv, SHORT_OPTS, LONG_OPTS,
                                    &opt_index)) != RC_END) {
        switch (opt_value) {
        case OPT_HELP:
            ADDFLAG(optmask, OPT_HELP);
            break;
        default:
            break;
        }
    }

    ARRAY(sources, SOURCES_MAX_COUNT, const char *) = {0};

    for (const char *arg = argv[optind]; optind < argc; arg = argv[++optind]) {
        ARRAY_ADD(sources, arg);
    }

    ARRAY_FOR(sources, idx) {
        const char *source_file = ARRAY_GET(sources, idx);
        IF_NOT_OK(badlang_compile_file(source_file), comp_rc) {
            LOG_ERROR("Failed to compile file: file=%s rc=%i\n", source_file,
                      comp_rc);
            return RC_FAIL;
        }
    }

    return RC_OK;
}
