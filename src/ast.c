#include "badlang/ast.h"

#include <nostdlib/types.h>
#include <nostdlib/macros.h>
#include <nostdlib/memory.h>

#include <stdio.h>

struct ast_node_trunk
ast_node_trunk_init(struct ast_node_trunk *prev, const char *str) {
    return (struct ast_node_trunk){
        .prev = prev,
        .str = str,
    };
}

void
ast_node_trunk_print(const struct ast_node_trunk *trunk) {
    if (trunk == nullptr) {
        return;
    }
    ast_node_trunk_print(trunk->prev);
    printf("%s", trunk->str);
}

void
ast_node_print(const struct ast_node *root, struct ast_node_trunk *prev,
               bool is_left) {
    if (root == nullptr) {
        return;
    }

    const char *prev_str = "    ";
    struct ast_node_trunk trunk = ast_node_trunk_init(prev, prev_str);

    ast_node_print(root->right, &trunk, true);

    if (!prev) {
        trunk.str = "———";
    } else if (is_left) {
        trunk.str = ".———";
        prev_str = "   |";
    } else {
        trunk.str = "`———";
        prev->str = prev_str;
    }

    ast_node_trunk_print(&trunk);

    if (root->value != nullptr) {
        char value[root->value->len + 1];
        noc_memory_copy(value, root->value->buf, root->value->len);

        printf(" %s(%s)\n", ast_node_type_to_str(root->type), value);
    } else {
        printf(" %s\n", ast_node_type_to_str(root->type));
    }

    if (prev) {
        prev->str = prev_str;
    }

    trunk.str = "   |";
    ast_node_print(root->left, &trunk, false);
}

const char *
ast_node_type_to_str(enum ast_node_type ast_node_type) {
    switch (ast_node_type) {
    case AST_NOP:
        return STRINGIFY(AST_NOP);
    case AST_MODULE:
        return STRINGIFY(AST_MODULE);
    case AST_OP_ID_ACCESS:
        return STRINGIFY(AST_OP_ID_ACCESS);
    case AST_OP_ASSIGNMENT:
        return STRINGIFY(AST_OP_ASSIGNMENT);
    case AST_COMP_ASSIGNMENT:
        return STRINGIFY(AST_COMP_ASSIGNMENT);
    case AST_DECL_VAR:
        return STRINGIFY(AST_DECL_VAR);
    case AST_DECL_VAR_IMPL:
        return STRINGIFY(AST_DECL_VAR_IMPL);
    case AST_DECL_FUNC:
        return STRINGIFY(AST_DECL_FUNC);
    case AST_EXPR_LITERAL:
        return STRINGIFY(AST_EXPR_LITERAL);
    }
    return "UNKNOWN";
}

struct ast_node
ast_node_init(enum ast_node_type type, const struct str* value, struct ast_node *left,
              struct ast_node *right) {
    return (struct ast_node){
        .type = type,
        .value = value,
        .left = left,
        .right = right,
    };
}

struct ast
ast_init(void) {
    return (struct ast){
        .root = nullptr,
    };
}

// static void ast_parse_block(struct ast *ast) {
//
// }

void
ast_parse(struct ast *ast, const struct token *tokens, u64 count) {
    const struct token *curtoken = tokens;

    while (curtoken->type != TOKEN_EOF) {
        curtoken++;
    }

    KEEP(ast);
    KEEP(tokens);
    KEEP(count);
}
