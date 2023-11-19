#include <stdlib.h>
#include "parser/parser.h"
#include "parser/ast_utils.h"

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

    for (int i = 0; i < root->child->size; i++) {
        // Parse each statement
        parseStatement(root->child->nodes[i]);
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
                pushASTNode(ast->child, stmt);
                initializeASTNode(&stmt, AST_NODE_TYPE_STMT);
            }
            // skip the end token
            continue;
        }

        // Add the token to the statement node.
        pushToken(stmt->tokens, ast->tokens->tokens[i]);
    }
}

void parseStatement(ASTNode *ast) {
    TokenStack *tokens;

    shuntingYard(&tokens, ast->tokens);

    // TODO: postfix to AST

    freeTokenStack(tokens);
}

void shuntingYard(TokenStack **dst, TokenStack *tokens) {
    TokenStack *objects, *operators;

    initializeTokenStack(&objects);
    initializeTokenStack(&operators);

    for (int i = 0; i < tokens->size; i++) {
        Token token = tokens->tokens[i];

        if (token.type == TOKEN_TYPE_OBJECT || token.type == TOKEN_TYPE_NUMBER || token.type == TOKEN_TYPE_STRING) {
            pushToken(objects, token);
        } else if (token.type == TOKEN_TYPE_BINARY_OPERATOR || token.type == TOKEN_TYPE_UNARY_OPERATOR) {
            while (operators->size > 0 && getPrecedence(operators->tokens[operators->size - 1].value) >= getPrecedence(token.value)) {
                pushToken(objects, popToken(operators));
            }
            pushToken(operators, token);
        } else if (token.type == TOKEN_TYPE_L_PAREN) {
            pushToken(operators, token);
        } else if (token.type == TOKEN_TYPE_R_PAREN) {
            while (operators->size > 0 && operators->tokens[operators->size - 1].type != TOKEN_TYPE_L_PAREN) {
                pushToken(objects, popToken(operators));
            }
            popToken(operators);
        }
    }

    while (operators->size > 0) {
        pushToken(objects, popToken(operators));
    }

    *dst = objects;

    freeTokenStack(operators);
}
