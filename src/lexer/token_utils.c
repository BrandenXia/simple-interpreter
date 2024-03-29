#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lexer/token.h"
#include "lexer/token_utils.h"
#include "lexer/char_utils.h"

inline const char *stringifyTokenType(TokenType type) {
    switch (type) {
        case TOKEN_TYPE_OBJECT:
            return "OBJECT";
        case TOKEN_TYPE_UNARY_OPERATOR:
            return "UNARY_OPERATOR";
        case TOKEN_TYPE_BINARY_OPERATOR:
            return "BINARY_OPERATOR";
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
        default:
            return "UNKNOWN";
    }
}

inline bool isUnaryOperator(const char *c) {
    return matchStringStart(c, UNARY_OPERATORS);
}

inline bool isBinaryOperator(const char *c) {
    return matchStringStart(c, BINARY_OPERATORS);
}

inline bool isRightParen(const char *c) {
    return inArrayChar(R_PARENS, *c) && strlen(c) == 1;
}

inline bool isLeftParen(const char *c) {
    return inArrayChar(L_PARENS, *c) && strlen(c) == 1;
}

bool isString(const char *c) {
    unsigned long len;

    len = strlen(c);

    if (inArrayChar(QUOTES, c[0])) {
        if (len == 1) return true;
        if (countChar(c, c[0]) == 2) return c[0] == c[len - 1];
        return true;
    }

    return false;
}

inline bool isEnd(const char *c) {
    return inArrayChar(ENDS, *c) && strlen(c) == 1;
}

inline bool isObject(const char *c) {
    return allChar(c, (bool (*)(char)) isalpha);
}

inline bool isNumber(const char *c) {
    return allChar(c, (bool (*)(char)) isdigit);
}

inline bool isBlank(const char *c) {
    return isspace(*c);
}

TokenType getType(const char *c) {
    if (isUnaryOperator(c)) {
        return TOKEN_TYPE_UNARY_OPERATOR;
    } else if (isBinaryOperator(c)) {
        return TOKEN_TYPE_BINARY_OPERATOR;
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
    char *escapedValue;

    unescape(&escapedValue, token->value);
    printf("Token(%s, \"%s\")\n", stringifyTokenType(token->type), escapedValue);
    free(escapedValue);
}

void printTokens(const TokenStack *tokens) {
    printf("TokenStack(%d) [\n", tokens->size);
    for (int i = 0; i < tokens->size; i++) {
        printf("\t");
        printToken(&tokens->tokens[i]);
    }
    printf("]\n");
}
