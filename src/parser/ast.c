#include <stdlib.h>
#include <string.h>
#include "parser/ast.h"

void initializeASTNode(ASTNode **dst, ASTNodeType type) {
    ASTNode *node;

    // Allocate memory for the node.
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

    // Free the tokens
    if (node->tokens != NULL) {
        free(node->tokens->value); // Free the value of the token
        free(node->tokens); // Free the token
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

void addASTNodeToken(ASTNode *node, Token *token) {
    Token *tmp;
    char *value;

    node->tokens_count++; // Increment the token count
    tmp = realloc(node->tokens, sizeof(Token) * node->tokens_count); // Reallocate the token array
    value = calloc(strlen(token->value) + 1, sizeof(char)); // Allocate memory for the value of the token
    if (tmp == NULL) {
        freeASTNode(node);
        exit(1);
    }
    strcpy(value, token->value); // Copy the value of the token
    node->tokens = tmp; // Set the token array to the new array
    node->tokens[node->tokens_count - 1] = *token; // Add the token to the array
    node->tokens[node->tokens_count - 1].value = value; // Assign the value of the token
}
