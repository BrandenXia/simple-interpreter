#ifndef SIMPLE_INTERPRETER_AST_H
#define SIMPLE_INTERPRETER_AST_H

#include "lexer/token.h"

/*
 * AST node types:
 * - AST_NODE_TYPE_PROGRAM: program
 * - AST_NODE_TYPE_STMT: statement
 * - AST_NODE_TYPE_EXPR: expression
 * - AST_NODE_TYPE_VAR: variable
 * - AST_NODE_TYPE_CONST: constant
 * - AST_NODE_TYPE_OP: operator
 */
typedef enum {
    AST_NODE_TYPE_PROGRAM,
    AST_NODE_TYPE_STMT,
    AST_NODE_TYPE_VAR,
    AST_NODE_TYPE_CONST,
    AST_NODE_TYPE_OP
} ASTNodeType;

/*
 * AST node:
 * - type: node type
 * - token: tokens
 * - token_count: number of tokens
 * - children: children nodes
 * - child_count: number of children nodes
 */
typedef struct ASTNode {
    ASTNodeType type;
    Token *tokens;
    int tokens_count;
    struct ASTNode **child;
    int child_count;
} ASTNode;

/*
 * Initialize an AST node.
 */
void initializeASTNode(ASTNode **dst, ASTNodeType type);

/*
 * Free an AST node.
 */
void freeASTNode(ASTNode *node);

/*
 * Add a child node to the parent node.
 */
void addASTNodeChild(ASTNode *parent, ASTNode *child);

/*
 * Add a token to the AST node.
 */
void addASTNodeToken(ASTNode *node, Token *token);

#endif //SIMPLE_INTERPRETER_AST_H
