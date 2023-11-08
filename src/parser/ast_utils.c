#include <stdio.h>
#include "lexer/token_utils.h"
#include "parser/ast_utils.h"

inline const char *stringifyASTNodeTypes(ASTNodeType type) {
    switch (type) {
        case AST_NODE_TYPE_PROGRAM:
            return "AST_NODE_TYPE_PROGRAM";
        case AST_NODE_TYPE_STMT:
            return "AST_NODE_TYPE_STMT";
        case AST_NODE_TYPE_EXPR:
            return "AST_NODE_TYPE_EXPR";
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

void printAST(ASTNode *root, int level) {
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
    for (int i = 0; i < root->tokens_count - 1; i++) {
        printf("%s ", stringifyTokenType(root->tokens[i].type));
    }
    printf("%s", stringifyTokenType(root->tokens[root->tokens_count - 1].type));
    printf(")");

    for (int i = 0; i < root->child_count; i++) {
        printf("\n");
        printAST(root->child[i], level + 1);
    }

    if (level == 0) {
        printf("\n");
    }
}
