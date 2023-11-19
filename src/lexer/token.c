#include <stdlib.h>
#include "lexer/token.h"

const char *UNARY_OPERATORS[] = {"!", ""};

const char *BINARY_OPERATORS[] = {"+", "-", "*", "/", "^", "%", "=", "==", "!=", ">", "<", ">=", "<=", "&&", "||", ""};

const char L_PARENS[] = "({[";

const char R_PARENS[] = ")}]";

const char QUOTES[] = "\"'";

const char ENDS[] = ";\n";

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
