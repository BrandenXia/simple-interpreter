#ifndef SIMPLE_INTERPRETER_AST_H
#define SIMPLE_INTERPRETER_AST_H

#include "lexer/token.h"

typedef enum {
    AST_NODE_TYPE_PROGRAM,
    AST_NODE_TYPE_STATEMENT,
    AST_NODE_TYPE_EXPRESSION,
    AST_NODE_TYPE_OBJECT,
    AST_NODE_TYPE_VALUE,
    AST_NODE_TYPE_OPERATOR,
    AST_NODE_TYPE_ASSIGNMENT
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    Token **tokens;
    int tokensSize;
    int childrenSize;
    struct ASTNode **children;
} ASTNode;

ASTNode *newASTNode();

void addASTNode(ASTNode *node, ASTNode *child);

extern const char *PAREN_MAP[];

#endif //SIMPLE_INTERPRETER_AST_H