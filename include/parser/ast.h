#ifndef SIMPLE_INTERPRETER_AST_H
#define SIMPLE_INTERPRETER_AST_H

#include "lexer/token.h"

typedef enum {
    AST_NODE_TYPE_PROGRAM,
    AST_NODE_TYPE_STMT,
    AST_NODE_TYPE_EXPR,
    AST_NODE_TYPE_VAR,
    AST_NODE_TYPE_CONST,
    AST_NODE_TYPE_OP
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    Token *token;
    int token_count;
    struct ASTNode **children;
    int child_count;
} ASTNode;

void initializeASTNode(ASTNode **dst, ASTNodeType type);

void freeASTNode(ASTNode *node);

void addASTNodeChild(ASTNode *parent, ASTNode *child);

void addASTNodeToken(ASTNode *node, Token *token);

#endif //SIMPLE_INTERPRETER_AST_H
