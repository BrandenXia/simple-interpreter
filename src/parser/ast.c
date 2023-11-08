#include <stdlib.h>
#include <string.h>
#include "parser/ast.h"

void initializeASTNode(ASTNode **dst, ASTNodeType type) {
    ASTNode *node;

    node = malloc(sizeof(ASTNode));
    node->type = type;
    node->tokens = NULL;
    node->tokens_count = 0;
    node->child = NULL;
    node->child_count = 0;

    *dst = node;
}

void freeASTNode(ASTNode *node) {
    int i;

    if (node->tokens != NULL) {
        free(node->tokens->value);
        free(node->tokens);
    }

    for (i = 0; i < node->child_count; i++) {
        freeASTNode(node->child[i]);
    }

    if (node->child != NULL) {
        free(node->child);
    }

    free(node);
}

void addASTNodeChild(ASTNode *parent, ASTNode *child) {
    ASTNode **tmp;

    parent->child_count++;
    tmp = realloc(parent->child, sizeof(ASTNode *) * parent->child_count);
    if (tmp == NULL) {
        freeASTNode(parent);
        exit(1);
    }
    parent->child = tmp;
    parent->child[parent->child_count - 1] = child;
}

void addASTNodeToken(ASTNode *node, Token *token) {
    Token *tmp;
    char *value;

    node->tokens_count++;
    tmp = realloc(node->tokens, sizeof(Token) * node->tokens_count);
    value = calloc(strlen(token->value) + 1, sizeof(char));
    if (tmp == NULL) {
        freeASTNode(node);
        exit(1);
    }
    strcpy(value, token->value);
    node->tokens = tmp;
    node->tokens[node->tokens_count - 1] = *token;
    node->tokens[node->tokens_count - 1].value = value;
}
