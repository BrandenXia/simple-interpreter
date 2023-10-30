#include <stdio.h>
#include "parser/ast_utils.h"

char *stringifyASTNodeType(const ASTNodeType type) {
    switch (type) {
        case AST_NODE_TYPE_PROGRAM:
            return "Program";
        case AST_NODE_TYPE_STATEMENT:
            return "Statement";
        case AST_NODE_TYPE_EXPRESSION:
            return "Expression";
        case AST_NODE_TYPE_OBJECT:
            return "Object";
        case AST_NODE_TYPE_VALUE:
            return "Value";
        case AST_NODE_TYPE_OPERATOR:
            return "Operator";
        case AST_NODE_TYPE_ASSIGNMENT:
            return "Assignment";
        default:
            return "Unknown";
    }
}

void printASTNode(const ASTNode *node, int depth) {
    int i;

    for (i = 0; i < depth - 1; i++) {
        printf("\t");
    }

    if (depth > 0) {
        printf("|-> ");
    }

    printf("%s\n", stringifyASTNodeType(node->type));

    for (i = 0; i < node->childrenSize; i++) {
        printASTNode(node->children[i], depth + 1);
    }
}