#include <stdlib.h>
#include "lexer/token.h"

const char *OPERATORS[] = {"+", "-", "*", "/", "^", "%", "=", "==", "!=", ">", "<", ">=", "<=", "&&", "||", "!", ""};

const char L_PARENS[] = "({[";

const char R_PARENS[] = ")}]";

const char QUOTES[] = "\"'";

const char ENDS[] = ";";

TokenList *newTokenList() {
    TokenList *list;

    list = malloc(sizeof(TokenList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

void addToken(TokenList *list, Token token) {
    TokenNode *node;

    node = malloc(sizeof(TokenNode));
    node->token = token;
    node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }

    list->tail = node;
    list->size++;
}

TokenStack *newTokenStack() {
    TokenStack *stack;

    stack = malloc(sizeof(TokenStack));
    stack->size = 0;
    stack->capacity = 1;
    stack->token = malloc(sizeof(Token *));

    return stack;
}

bool isTokenStackEmpty(const TokenStack *stack) {
    return stack->size == 0;
}

bool isTokenStackFull(const TokenStack *stack) {
    return stack->size == stack->capacity;
}

void pushToken(TokenStack *stack, Token *token) {
    Token **tmp;

    if (isTokenStackFull(stack)) {
        stack->capacity *= 2;
        tmp = realloc(stack->token, sizeof(Token *) * stack->capacity);
        if (tmp == NULL) {
            free(stack->token);
            exit(1);
        }
        stack->token = tmp;
    }

    stack->token[stack->size] = token;
    stack->size++;
}

Token *popToken(TokenStack *stack) {
    Token *token;

    if (isTokenStackEmpty(stack)) {
        return NULL;
    }

    token = stack->token[stack->size - 1];
    stack->size--;

    return token;
}

const Token *peekToken(const TokenStack *stack) {
    if (isTokenStackEmpty(stack)) {
        return NULL;
    }

    return stack->token[stack->size - 1];
}