#include <stdlib.h>
#include <string.h>
#include "parser/ast.h"

void initializeASTNode(ASTNode **dst, ASTNodeType type) {
    ASTNode *node;

    // Allocate memory for the node.
    node = malloc(sizeof(ASTNode));
    node->type = type;
    initializeTokenStack(&node->tokens);
    node->child = NULL;
    node->child_count = 0;

    *dst = node;
}

void freeASTNode(ASTNode *node) {
    int i;

    // Free the tokens
    if (node->tokens != NULL) {
        freeTokenStack(node->tokens);
    }

    for (i = 0; i < node->child_count; i++) {
        freeASTNode(node->child[i]); // Free the child node
    }

    if (node->child != NULL) {
        free(node->child); // Free the child array
    }

    free(node); // Free the node itself
}

void addASTNodeChild(ASTNode *parent, ASTNode *child) {
    ASTNode **tmp;

    parent->child_count++; // Increment the child count
    tmp = realloc(parent->child, sizeof(ASTNode *) * parent->child_count); // Reallocate the child array
    if (tmp == NULL) {
        freeASTNode(parent);
        exit(1);
    }
    parent->child = tmp; // Set the child array to the new array
    parent->child[parent->child_count - 1] = child; // Add the child to the array
}
