#include <stdlib.h>
#include <string.h>
#include "parser/ast.h"

void initializeASTNode(ASTNode **dst, ASTNodeType type) {
    ASTNode *node;

    // Allocate memory for the node.
    node = malloc(sizeof(ASTNode));
    node->type = type;
    initializeTokenStack(&node->tokens);
    initializeASTNodeStack(&node->child);

    *dst = node;
}

void freeASTNode(ASTNode *node) {
    // Free the tokens
    if (node->tokens != NULL) freeTokenStack(node->tokens);

    // Free the children
    if (node->child != NULL) freeASTNodeStack(node->child);

    free(node); // Free the node itself
}

void initializeASTNodeStack(ASTNodeStack **dst) {
    ASTNodeStack *tmp;

    tmp = malloc(sizeof(ASTNodeStack));
    tmp->nodes = malloc(sizeof(ASTNode *));
    tmp->size = 0;
    tmp->capacity = 1;

    *dst = tmp;
}

void freeASTNodeStack(ASTNodeStack *stack) {
    for (int i = 0; i < stack->size; i++) {
        freeASTNode(stack->nodes[i]);
    }

    free(stack->nodes);
    free(stack);
}

void pushASTNode(ASTNodeStack *stack, ASTNode *node) {
    ASTNode **tmp;

    if (stack->size == stack->capacity) {
        stack->capacity *= 2;
        tmp = realloc(stack->nodes, stack->capacity * sizeof(ASTNode *));
        if (tmp == NULL) exit(1);
        stack->nodes = tmp;
    }

    stack->nodes[stack->size++] = node;
}

inline ASTNode *popASTNode(ASTNodeStack *stack) {
    return stack->nodes[--stack->size];
}

inline ASTNode *peekASTNode(ASTNodeStack *stack) {
    return stack->nodes[stack->size - 1];
}
