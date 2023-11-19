#ifndef SIMPLE_INTERPRETER_AST_H
#define SIMPLE_INTERPRETER_AST_H

#include "lexer/token.h"

struct ASTNode;

struct ASTNodeStack;

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
 * - tokens: tokens stack
 * - children: children nodes
 * - child_count: number of children nodes
 */
typedef struct ASTNode {
    ASTNodeType type;
    TokenStack *tokens;
    struct ASTNodeStack *child;
} ASTNode;

typedef struct ASTNodeStack {
    ASTNode **nodes;
    int size;
    int capacity;
} ASTNodeStack;

/*
 * Initialize an AST node.
 */
void initializeASTNode(ASTNode **dst, ASTNodeType type);

/*
 * Free an AST node.
 */
void freeASTNode(ASTNode *node);

/*
 * Initialize an ASTNodeStack.
 */
void initializeASTNodeStack(ASTNodeStack **dst);

/*
 * Free an ASTNodeStack.
 */
void freeASTNodeStack(ASTNodeStack *stack);

/*
 * Push an AST node to an ASTNodeStack.
 */
void pushASTNode(ASTNodeStack *stack, ASTNode *node);

/*
 * Pop an AST node from an ASTNodeStack.
 * This function will return memory address of the popped node, remember to free it.
 */
ASTNode *popASTNode(ASTNodeStack *stack);

/*
 * Peek an AST node from an ASTNodeStack.
 * This function will return memory address of the peeked node, do not free it because it's still in the stack.
 */
ASTNode *peekASTNode(ASTNodeStack *stack);

#endif //SIMPLE_INTERPRETER_AST_H
