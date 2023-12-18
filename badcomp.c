/*
 * BADCOMP
 *
 * */
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#else
#include <unistd.h>
#endif

#define KEEP(__X) ((void)(__X))

#define MKFLAG(__X) (1 << (__X))
#define ADDFLAG(__MASK, __X) ((__MASK) |= (__X))

#define MAX_SOURCES_COUNT 1024
#define MAX_TOKENS_COUNT 4096

#define LOG_ERROR(...) fprintf(stderr, __VA_ARGS__)

#define ARRAY(__NAME, __SIZE, __TYPE)                                          \
    struct {                                                                   \
        __TYPE _items[(__SIZE)];                                               \
        uint64_t _length;                                                      \
    } __NAME

#define ARRAY_ADD(__ARRAY, __ITEM)                                             \
    (__ARRAY)._items[(__ARRAY)._length++] = __ITEM

#define ARRAY_LEN(__ARRAY) ((__ARRAY)._length)

#define ARRAY_GET(__ARRAY, __IDX) ((__ARRAY)._items[(__IDX)])

#define ARRAY_FOR(__ARRAY, __IDX)                                              \
    for (uint64_t __IDX = 0; __IDX < ARRAY_LEN(__ARRAY); ++__IDX)

enum rc {
    RC_END = -1,
    RC_OK = EXIT_SUCCESS,
    RC_FAIL = EXIT_FAILURE,
};

#define IF_NOT_OK(__EXPR, __RCNAME)                                            \
    enum rc __RCNAME = RC_OK;                                                  \
    if ((__RCNAME = (__EXPR)) != RC_OK)

enum opt {
    OPT_NONE = MKFLAG(0),
    OPT_HELP = MKFLAG(1),
};

enum token_type {
    TOK_UNEXPECED = 0,
};

struct token {
    const char *value;
    enum token_type type;
};

static const struct option LONG_OPTS[] = {
    {"help", false, NULL, OPT_HELP},
};

static const char *SHORT_OPTS = "h";

bool
fs_is_exists(const char *p) {
    return access(p, F_OK) == RC_OK;
}

enum rc
parse_source(const char *source, struct token *tokens, size_t tokens_capacity) {



    return RC_OK;
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

    ARRAY(sources, MAX_SOURCES_COUNT, const char *) = {0};

    for (const char *arg = argv[optind]; optind < argc; arg = argv[++optind]) {
        ARRAY_ADD(sources, arg);
    }

    ARRAY(nonexisting_sources, MAX_SOURCES_COUNT, const char *) = {0};
    ARRAY_FOR(sources, i) {
        const char *source_file = ARRAY_GET(sources, i);
        if (fs_is_exists(source_file)) {
            continue;
        }
        ARRAY_ADD(nonexisting_sources, source_file);
    }

    if (ARRAY_LEN(nonexisting_sources) > 0) {
        LOG_ERROR("Got non-existing sources!\n");
        ARRAY_FOR(nonexisting_sources, i) {
            LOG_ERROR("  [%lu]: %s\n", i, ARRAY_GET(nonexisting_sources, i));
        }
        return RC_FAIL;
    }

    struct token *tokens = calloc(MAX_TOKENS_COUNT, sizeof(struct token));

    IF_NOT_OK(parse_source(ARRAY_GET(sources, 0), tokens, MAX_TOKENS_COUNT) !=
                  RC_OK,
              parse_source_rc) {
        LOG_ERROR("parse_source() fails with %i rc\n", parse_source_rc);

        free(tokens);
        return RC_FAIL;
    }

    free(tokens);
    return RC_OK;
}
