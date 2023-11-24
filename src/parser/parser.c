#include <stdlib.h>
#include "parser/parser.h"
#include "parser/ast_utils.h"

void parse(ASTNode **dst, TokenStack *tokens) {
    ASTNode *root;

    // Initialize the root node
    initializeASTNode(&root, AST_NODE_TYPE_PROGRAM);

    // Add all tokens to the root node
    root->tokens = tokens;

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
    ASTNodeStack *nodes;

    // Convert the statement into a postfix token stack.
    shuntingYard(&tokens, ast->tokens);

    // Initialize the AST node stack.
    initializeASTNodeStack(&nodes);

    for (int i = 0; i < tokens->size; i++) {
        // Get the token.
        Token token = tokens->tokens[i];

        ASTNode *node;

        if (token.type == TOKEN_TYPE_OBJECT) {
            initializeASTNode(&node, AST_NODE_TYPE_VAR);
        } else if (token.type == TOKEN_TYPE_NUMBER || token.type == TOKEN_TYPE_STRING) {
            initializeASTNode(&node, AST_NODE_TYPE_CONST);
        } else if (token.type == TOKEN_TYPE_BINARY_OPERATOR) {
            initializeASTNode(&node, AST_NODE_TYPE_OP);

            // Pop the right and left operands.
            ASTNode *right = popASTNode(nodes);
            ASTNode *left = popASTNode(nodes);

            if (right == NULL || left == NULL) {
                ASTNode *error;
                initializeASTNode(&error, AST_NODE_TYPE_ERROR);
                pushASTNode(nodes, error);
                break;
            }

            // Push the operands to the operator node.
            pushASTNode(node->child, left);
            pushASTNode(node->child, right);
        } else if (token.type == TOKEN_TYPE_UNARY_OPERATOR) {
            initializeASTNode(&node, AST_NODE_TYPE_OP);

            // Pop the operand.
            ASTNode *operand = popASTNode(nodes);

            // Push the operand to the operator node.
            pushASTNode(node->child, operand);
        } else {
            continue;
        }

        // Push the token to the node.
        pushToken(node->tokens, token);
        // Push the node to the stack.
        pushASTNode(nodes, node);
    }

    // Free the old tokens and nodes.
    freeASTNodeStack(ast->child);
    // Set the new tokens and nodes.
    ast->child = nodes;

    // Free the postfix token stack.
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
            while (operators->size > 0 &&
                   getPrecedence(operators->tokens[operators->size - 1].value) >= getPrecedence(token.value)) {
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
        } else if (token.type == TOKEN_TYPE_UNKNOWN) {
            freeTokenStack(objects);
            freeTokenStack(operators);

            TokenStack *tmp;
            initializeTokenStack(&tmp);
            *dst = tmp;

            return;
        }
    }

    while (operators->size > 0) {
        pushToken(objects, popToken(operators));
    }

    *dst = objects;

    freeTokenStack(operators);
}
