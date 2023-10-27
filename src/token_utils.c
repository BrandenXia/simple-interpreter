#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "token.h"
#include "token_utils.h"
#include "char_utils.h"

bool isOperator(char *c) {
    for (int i = 0; OPERATORS[i][0] != '\0'; i++) {
        if (strcmp(OPERATORS[i], c) == 0 || strcmp(strncpy(malloc(sizeof(char)), OPERATORS[i], 1), c) == 0) {
            return true;
        }
    }
    return false;
}

bool isRightParen(char c) {
    return inArrayChar(R_PARENS, c);
}

bool isLeftParen(char c) {
    return inArrayChar(L_PARENS, c);
}

bool isQuote(char c) {
    return inArrayChar(QUOTES, c);
}

bool isEnd(char c) {
    return inArrayChar(ENDS, c);
}

bool isObject(char *c) {
    for (int i = 0; i < strlen(c); i++) {
        if (!isAlpha(c[i])) {
            return false;
        }
    }

    return true;
}

bool isNumber(char *c) {
    for (int i = 0; i < strlen(c); i++) {
        if (!isDigit(c[i])) {
            return false;
        }
    }

    return true;
}

bool isBlank(char *c) {
    while (*c != '\0') {
        if (!isspace(*c)) {
            return false;
        }
        c++;
    }

    return true;
}

TokenType getType(char *c) {
    if (isOperator(c)) {
        return OPERATOR;
    } else if (isRightParen(*c)) {
        return R_PAREN;
    } else if (isLeftParen(*c)) {
        return L_PAREN;
    } else if (isQuote(*c)) {
        return STRING;
    } else if (isEnd(*c)) {
        return END;
    } else if (isObject(c)) {
        return OBJECT;
    } else if (isNumber(c)) {
        return NUMBER;
    } else if (isBlank(c)) {
        return BLANK;
    } else {
        return UNKNOWN;
    }
}

void printToken(Token *token) {
    printf("Token(%s, \"%s\")\n", tokenTypeToString(token->type), token->value);
}

void printTokens(TokenList *tokens) {
    printf("TokenList(%d) [\n", tokens->size);
    for (TokenNode *current = tokens->head; current != NULL; current = current->next) {
        printf("\t");
        printToken(&current->data);
    }
    printf("]\n");
}