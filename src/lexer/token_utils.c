#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lexer/token.h"
#include "lexer/token_utils.h"
#include "lexer/char_utils.h"

inline const char *stringifyTokenType(TokenType type) {
    switch (type) {
        case TOKEN_TYPE_OBJECT:
            return "OBJECT";
        case TOKEN_TYPE_OPERATOR:
            return "OPERATOR";
        case TOKEN_TYPE_NUMBER:
            return "NUMBER";
        case TOKEN_TYPE_STRING:
            return "STRING";
        case TOKEN_TYPE_L_PAREN:
            return "L_PAREN";
        case TOKEN_TYPE_R_PAREN:
            return "R_PAREN";
        case TOKEN_TYPE_END:
            return "END";
        case TOKEN_TYPE_BLANK:
            return "BLANK";
        case TOKEN_TYPE_UNKNOWN:
            return "UNKNOWN";
    }
    return "UNKNOWN";
}

bool isOperator(const char *c) {
    for (int i = 0; OPERATORS[i][0] != '\0'; i++) {
        if (strcmp(OPERATORS[i], c) == 0 || strcmp(strncpy(malloc(sizeof(char)), OPERATORS[i], 1), c) == 0) {
            return true;
        }
    }
    return false;
}

bool isRightParen(const char *c) {
    if (strlen(c) != 1) return false;
    return inArrayChar(R_PARENS, *c);
}

bool isLeftParen(const char *c) {
    if (strlen(c) != 1) return false;
    return inArrayChar(L_PARENS, *c);
}

bool isString(const char *c) {
    unsigned long len;

    len = strlen(c);

    if (inArrayChar(QUOTES, c[0])) {
        if (len == 1) return true;
        if (countChar(c, c[0]) == 2) {
            return c[0] == c[len - 1];
        }
        return true;
    }

    return false;
}

bool isEnd(const char *c) {
    if (strlen(c) != 1) return false;
    return inArrayChar(ENDS, *c);
}

bool isObject(const char *c) {
    for (int i = 0; i < (int) strlen(c); i++) {
        if (!isAlpha(c[i])) {
            return false;
        }
    }

    return true;
}

bool isNumber(const char *c) {
    for (int i = 0; i < (int) strlen(c); i++) {
        if (!isDigit(c[i])) {
            return false;
        }
    }

    return true;
}

bool isBlank(const char *c) {
    while (*c != '\0') {
        if (!isspace(*c)) {
            return false;
        }
        c++;
    }

    return true;
}

TokenType getType(const char *c) {
    if (isOperator(c)) {
        return TOKEN_TYPE_OPERATOR;
    } else if (isRightParen(c)) {
        return TOKEN_TYPE_R_PAREN;
    } else if (isLeftParen(c)) {
        return TOKEN_TYPE_L_PAREN;
    } else if (isString(c)) {
        return TOKEN_TYPE_STRING;
    } else if (isEnd(c)) {
        return TOKEN_TYPE_END;
    } else if (isObject(c)) {
        return TOKEN_TYPE_OBJECT;
    } else if (isNumber(c)) {
        return TOKEN_TYPE_NUMBER;
    } else if (isBlank(c)) {
        return TOKEN_TYPE_BLANK;
    } else {
        return TOKEN_TYPE_UNKNOWN;
    }
}

void printToken(const Token *token) {
    printf("Token(%s, \"%s\")\n", stringifyTokenType(token->type), token->value);
}

void printTokens(const TokenList *tokens) {
    printf("TokenList(%d) [\n", tokens->size);
    for (TokenNode *current = tokens->head; current != NULL; current = current->next) {
        printf("\t");
        printToken(&current->token);
    }
    printf("]\n");
}