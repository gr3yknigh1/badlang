#ifndef BADLANG_AST_H_
#define BADLANG_AST_H_

#include "badlang/token.h"

struct ast_node_trunk {
    struct ast_node_trunk *prev;
    const char *str;
};

struct ast_node_trunk ast_node_trunk_init(struct ast_node_trunk *prev,
                                          const char *str);

void ast_node_trunk_print(const struct ast_node_trunk *trunk);

enum ast_node_type {
    AST_NOP,

    AST_MODULE,

    AST_OP_ID_ACCESS,
    AST_OP_ASSIGNMENT,

    AST_COMP_ASSIGNMENT,

    AST_DECL_VAR,
    AST_DECL_VAR_IMPL, // NOTE: With type deduce

    AST_DECL_FUNC,
    AST_EXPR_LITERAL,
};

const char *ast_node_type_to_str(enum ast_node_type ast_node_type);

struct ast_node {
    enum ast_node_type type;
    const struct str *value;

    struct ast_node *left;
    struct ast_node *right;
};

void ast_node_print(const struct ast_node *root, struct ast_node_trunk *prev,
                    bool is_left);

struct ast_node ast_node_init(enum ast_node_type type, const struct str* value, struct ast_node *left,
                              struct ast_node *right);

struct ast {
    struct ast_node *root;
};

struct ast ast_init(void);

void ast_parse(struct ast *ast, const struct token *tokens, u64 count);

#endif // BADLANG_AST_H_
