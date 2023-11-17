#include <stdlib.h>
#include "lexer/token.h"

const char *UNARY_OPERATORS[] = {"!", ""};

const char *BINARY_OPERATORS[] = {"+", "-", "*", "/", "^", "%", "=", "==", "!=", ">", "<", ">=", "<=", "&&", "||", ""};

const char L_PARENS[] = "({[";

const char R_PARENS[] = ")}]";

const char QUOTES[] = "\"'";

const char ENDS[] = ";\n";

void initializeTokenList(TokenList **dst) {
    TokenList *list;

    list = malloc(sizeof(TokenList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    *dst = list;
}

void freeTokenList(TokenList *list) {
    TokenNode *node, *next;

    for (node = list->head; node != NULL;) {
        next = node->next;
        free(node->token.value);
        free(node);
        node = next;
    }

    free(list);
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

void initializeTokenStack(TokenStack **dst) {
    TokenStack *stack;

    stack = malloc(sizeof(TokenStack));
    stack->tokens = malloc(sizeof(Token));
    stack->size = 0;
    stack->capacity = 1;

    *dst = stack;
}

void freeTokenStack(TokenStack *stack) {
    free(stack->tokens);
    free(stack);
}

void pushToken(TokenStack *stack, Token token) {
    Token *tmp;

    if (stack->size == stack->capacity) {
        stack->capacity *= 2;
        tmp = realloc(stack->tokens, stack->capacity * sizeof(Token));
        if (tmp == NULL) {
            freeTokenStack(stack);
            exit(1);
        }
        stack->tokens = tmp;
    }

    stack->tokens[stack->size] = token;
    stack->size++;
}

Token popToken(TokenStack *stack) {
    Token token;

    if (stack->size == 0) {
        token.type = TOKEN_TYPE_UNKNOWN;
        token.value = NULL;
        return token;
    }

    token = stack->tokens[stack->size - 1];
    stack->size--;

    return token;
}

Token peekToken(TokenStack *stack) {
    Token token;

    if (stack->size == 0) {
        token.type = TOKEN_TYPE_UNKNOWN;
        token.value = NULL;
        return token;
    }

    token = stack->tokens[stack->size - 1];

    return token;
}
