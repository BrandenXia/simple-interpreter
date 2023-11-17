#include <stdlib.h>
#include "parser/parser.h"

void parse(ASTNode **dst, TokenList *tokens) {
    ASTNode *root;

    // Initialize the root node
    initializeASTNode(&root, AST_NODE_TYPE_PROGRAM);

    // Add all tokens to the root node
    for (TokenNode *current = tokens->head; current != NULL; current = current->next) {
        pushToken(root->tokens, current->token);
    }

    // Parse the program to statements
    parseProgram(root);

    for (int i = 0; i < root->child_count; i++) {
        // Parse each statement
//        parseStatement(root->child[i]);
    }

    *dst = root;
}

void parseProgram(ASTNode *ast) {
    ASTNode *stmt;

    // Initialize the statement node.
    initializeASTNode(&stmt, AST_NODE_TYPE_STMT);

    // Add all tokens to the statement node.
    for (int i = 0; i < ast->tokens->size; i++) {
        // If it's the end of the statement, add the statement node to the AST and initialize a new statement node.
        if (ast->tokens->tokens[i].type == TOKEN_TYPE_END) {
            if (stmt->tokens->size > 0) {
                addASTNodeChild(ast, stmt);
                initializeASTNode(&stmt, AST_NODE_TYPE_STMT);
            }
            // skip the end token
            continue;
        }

        // Add the token to the statement node.
        pushToken(stmt->tokens, ast->tokens->tokens[i]);
    }
}
