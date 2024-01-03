/*
 * BADCOMP
 *
 * */
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <getopt.h>
#include <string_view>

#include "badlang/Bits.hpp"
#include "badlang/Macros.hpp"

#define SOURCES_MAX_COUNT 32
#define TOKENS_MAX_COUNT 1024

typedef enum {
    RC_END = -1,
    RC_OK = 0,
    RC_FAIL = 1,

    RC_FILE_NOT_FOUND,
    RC_FILE_FAIL_TO_OPEN,
} rc_t;

#define IF_NOT_OK(__EXPR, __RCNAME)                                            \
    enum rc __RCNAME = RC_OK;                                                  \
    if ((__RCNAME = (__EXPR)) != RC_OK)

enum opt {
    OPT_NONE = MKFLAG(0),
    OPT_HELP = MKFLAG(1),
};

static const struct option LONG_OPTS[] = {
    {"help", false, NULL, OPT_HELP},
};

static const char *SHORT_OPTS = "h";

static rc_t
Compile(const std::string_view source_content) {
    struct lexer lexer = lexer_init(source, size);
    struct Token *tokens = calloc(TOKENS_MAX_COUNT, sizeof(struct token));
    u64 tokens_count = lexer_parse(&lexer, tokens);

    struct ast ast = ast_init();
    struct ast_node ast_root = ast_node_init(AST_MODULE, null, null, null);
    ast_parse(&ast, tokens, tokens_count);

    ast_node_print(&ast_root, NULL, false);

    struct Token *token = tokens;
    char *token_value = NULL;
    while (token->type != TOKEN_EOF) {

        token_value = realloc(token_value, token->value.len + 1);
        memory_copy(token_value, token->value.buf, token->value.len);
        token_value[token->value.len] = '\0';

        printf("Token(value=[%s] type=%s)\n", token_value,
               token_type_to_str(token->type));

        token_free(token);
        token++;
    }

    return RC_OK;
}

static rc_t
CompileFile(const std::filesystem::path &source_path) {
    if (!std::filesystem::exists(source_path)) {
        return RC_FILE_NOT_FOUND;
    }

    FILE *f = fopen(source_file, "r");

    if (f == NULL) {
        return RC_FILE_FAIL_TO_OPEN;
    }

    size_t file_size = fs_file_size(f);
    char *file_content = malloc(file_size * sizeof(char) + 1);
    fread(file_content, file_size, 1, f);
    file_content[file_size] = '\0';

    enum rc_t rc = Compile(file_content, file_size);

    free(file_content);

    return rc;
}

int
main(int argc, char *const *argv) {
    KEEP(argc);

    std::vector<std::filesystem::path> sources;
    sources.push_back(argv[1]);

    for (const auto &source : sources) {
        Compile()
    }

    // ARRAY_FOR(sources, idx) {
    //     const char *source_file = ARRAY_GET(sources, idx);
    //     IF_NOT_OK(badlang_compile_file(source_file), comp_rc) {
    //         LOG_ERROR("Failed to compile file: file=%s rc=%i\n", source_file,
    //                   comp_rc);
    //         return RC_FAIL;
    //     }
    // }

    return RC_OK;
}
