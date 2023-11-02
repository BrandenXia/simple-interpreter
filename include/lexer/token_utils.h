#ifndef SIMPLE_INTERPRETER_TOKEN_UTILS_H
#define SIMPLE_INTERPRETER_TOKEN_UTILS_H

#include <stdbool.h>

const char *stringifyTokenType(TokenType type);

bool isOperator(const char *c);

bool isRightParen(const char *c);

bool isLeftParen(const char *c);

bool isString(const char *c);

bool isEnd(const char *c);

bool isObject(const char *c);

bool isNumber(const char *c);

bool isBlank(const char *c);

TokenType getType(const char *c);

void printToken(const Token *token);

void printTokens(const TokenList *tokens);

#endif //SIMPLE_INTERPRETER_TOKEN_UTILS_H
