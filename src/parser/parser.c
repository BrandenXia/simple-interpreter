#include <stdlib.h>
#include <string.h>
#include "parser/parser.h"

ASTNode *parse(const TokenList *tokens) {
    ASTNode *root;

    root = parseStatements(tokens);

    return root;
}

ASTNode *parseStatements(const TokenList *tokens) {
    ASTNode *root, *statement;
    TokenStack *statementStack;

    root = newASTNode();
    root->type = AST_NODE_TYPE_PROGRAM;
    statement = newASTNode();
    statement->type = AST_NODE_TYPE_STATEMENT;
    statementStack = newTokenStack();

    for (TokenNode *current = tokens->head; current != NULL; current = current->next) {
        if (current->token.type == TOKEN_TYPE_END) {
            if (isTokenStackEmpty(statementStack)) continue;
            statement->tokens = statementStack->token;
            statement->tokensSize = statementStack->size;
            addASTNode(root, statement);
            statement = newASTNode();
            statement->type = AST_NODE_TYPE_STATEMENT;
            free(statementStack);
            statementStack = newTokenStack();
            continue;
        }

        pushToken(statementStack, &current->token);
    }
    free(statementStack);

    return root;
}