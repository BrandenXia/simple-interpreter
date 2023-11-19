#include <stdio.h>
#include <string.h>
#include "lexer/token_utils.h"
#include "parser/ast_utils.h"

inline const char *stringifyASTNodeTypes(ASTNodeType type) {
    switch (type) {
        case AST_NODE_TYPE_PROGRAM:
            return "AST_NODE_TYPE_PROGRAM";
        case AST_NODE_TYPE_STMT:
            return "AST_NODE_TYPE_STMT";
        case AST_NODE_TYPE_VAR:
            return "AST_NODE_TYPE_VAR";
        case AST_NODE_TYPE_CONST:
            return "AST_NODE_TYPE_CONST";
        case AST_NODE_TYPE_OP:
            return "AST_NODE_TYPE_OP";
        default:
            return "AST_NODE_TYPE_UNKNOWN";
    }
}

int getPrecedence(const char *op) {
    if (strcmp(op, "=") == 0) {
        return 0;
    } else if (strcmp(op, "&&") == 0) {
        return 1;
    } else if (strcmp(op, "||") == 0) {
        return 2;
    } else if (strcmp(op, "==") == 0 || strcmp(op, "!=") == 0) {
        return 3;
    } else if (strcmp(op, "<") == 0 || strcmp(op, ">") == 0 || strcmp(op, "<=") == 0 || strcmp(op, ">=") == 0) {
        return 4;
    } else if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) {
        return 5;
    } else if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0 || strcmp(op, "%") == 0) {
        return 6;
    } else if (strcmp(op, "^") == 0) {
        return 7;
    } else if (strcmp(op, "!") == 0) {
        return 8;
    } else {
        return -1;
    }
}

void printAST(const ASTNode *root, int level) {
    for (int i = 0; i < level; i++) {
        printf("\t");
    }

    if (level > 0) {
        printf("|- ");
    }

    // Print the type of the node
    printf("%s", stringifyASTNodeTypes(root->type));

    // Print type of the tokens
    printf(" (");
    for (int i = 0; i < root->tokens->size - 1; i++) {
        printf("%s ", stringifyTokenType(root->tokens->tokens[i].type));
    }
    printf("%s", stringifyTokenType(root->tokens->tokens[root->tokens->size - 1].type));
    printf(")");

    for (int i = 0; i < root->child->size; i++) {
        printf("\n");
        printAST(root->child->nodes[i], level + 1);
    }

    // If it's the root node, print a newline at the end
    if (level == 0) {
        printf("\n");
    }
}
