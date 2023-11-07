#include <stdlib.h>
#include "parser/ast.h"

void initializeASTNode(ASTNode **dst, ASTNodeType type) {
    ASTNode *node;

    node = malloc(sizeof(ASTNode));
    node->type = type;
    node->token = NULL;
    node->token_count = 0;
    node->children = NULL;
    node->child_count = 0;

    *dst = node;
}

void freeASTNode(ASTNode *node) {
    int i;

    if (node->token != NULL) {
        free(node->token);
    }

    for (i = 0; i < node->child_count; i++) {
        freeASTNode(node->children[i]);
    }

    if (node->children != NULL) {
        free(node->children);
    }

    free(node);
}

void addASTNodeChild(ASTNode *parent, ASTNode *child) {
    ASTNode **tmp;

    parent->child_count++;
    tmp = realloc(parent->children, sizeof(ASTNode *) * parent->child_count);
    if (tmp == NULL) {
        freeASTNode(parent);
        exit(1);
    }
    parent->children = tmp;
    parent->children[parent->child_count - 1] = child;
}

void addASTNodeToken(ASTNode *node, Token *token) {
    Token *tmp;

    node->token_count++;
    tmp = realloc(node->token, sizeof(Token) * node->token_count);
    if (tmp == NULL) {
        freeASTNode(node);
        exit(1);
    }
    node->token = tmp;
    node->token[node->token_count - 1] = *token;
}
