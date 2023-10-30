#include <stdlib.h>
#include <string.h>
#include "parser/ast.h"

ASTNode *newASTNode() {
    ASTNode *node;

    node = malloc(sizeof(ASTNode));
    node->type = AST_NODE_TYPE_PROGRAM;
    node->tokens = NULL;
    node->tokensSize = 0;
    node->childrenSize = 0;
    node->children = NULL;

    return node;
}

void addASTNode(ASTNode *node, ASTNode *child) {
    ASTNode **tmp;

    if (node->childrenSize == 0) {
        node->children = malloc(sizeof(ASTNode *));
    } else {
        tmp = realloc(node->children, sizeof(ASTNode *) * (node->childrenSize + 1));
        if (tmp == NULL) {
            free(node->children);
            exit(1);
        }
        node->children = tmp;
    }

    node->children[node->childrenSize] = child;
    node->childrenSize++;
}

int operatorPrecedence(const char *operator) {
    if (strcmp(operator, "=") == 0) {
        return 0;
    } else if (strcmp(operator, "||") == 0) {
        return 1;
    } else if (strcmp(operator, "&&") == 0) {
        return 2;
    } else if (strcmp(operator, "==") == 0 || strcmp(operator, "!=") == 0) {
        return 3;
    } else if (strcmp(operator, ">") == 0 || strcmp(operator, "<") == 0 || strcmp(operator, ">=") == 0 ||
               strcmp(operator, "<=") == 0) {
        return 4;
    } else if (strcmp(operator, "+") == 0 || strcmp(operator, "-") == 0) {
        return 5;
    } else if (strcmp(operator, "*") == 0 || strcmp(operator, "/") == 0 || strcmp(operator, "%") == 0) {
        return 6;
    } else if (strcmp(operator, "^") == 0) {
        return 7;
    } else if (strcmp(operator, "!") == 0) {
        return 8;
    } else {
        return -1;
    }
}

const char *PAREN_MAP[] = {
        "()",
        "[]",
        "{}",
        ""
};