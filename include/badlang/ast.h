#ifndef BADLANG_AST_H_
#define BADLANG_AST_H_

#include <nostdlib/types.h>

#include "badlang/token.h"

typedef struct ast_node_trunk {
    struct ast_node_trunk *prev;
    const char *str;
} ast_node_trunk_t;

ast_node_trunk_t ast_node_trunk_init(ast_node_trunk_t *prev, const char *str);

void ast_node_trunk_print(const ast_node_trunk_t *trunk);

typedef enum {
    AST_NOP,

    AST_MODULE,

    AST_RETURN,
    AST_COMPTIME_ASSIGNMENT,


    AST_LITERAL,
} ast_node_type_t;

const char *ast_node_type_to_str(ast_node_type_t ast_node_type);

typedef struct ast_node {
    ast_node_type_t type;

    const str_t *value;

    union {
        struct {
            struct ast_node *left;
            struct ast_node *middle;
            struct ast_node *right;
        };
        struct {
            struct ast_node *nodes;
            u64 nodes_count;
            u64 nodes_capacity;
        };
    };
} ast_node_t;

void ast_node_print(const ast_node_t *root, ast_node_trunk_t *prev,
                    bool is_left);

ast_node_t ast_node_init(ast_node_type_t type, const str_t *value,
                         ast_node_t *left, ast_node_t *right);

typedef struct {
    ast_node_t *root;
} ast_t;

ast_t ast_init(void);

void ast_parse(ast_t *ast, const token_t *tokens, u64 count);

#endif // BADLANG_AST_H_
