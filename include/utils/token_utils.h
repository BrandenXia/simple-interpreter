#ifndef SIMPLE_INTERPRETER_TOKEN_UTILS_H
#define SIMPLE_INTERPRETER_TOKEN_UTILS_H

#include <stdbool.h>

bool isOperator(char *c);

bool isRightParen(char c);

bool isLeftParen(char c);

bool isQuote(char c);

bool isEnd(char c);

bool isObject(char *c);

bool isNumber(char *c);

bool isBlank(char *c);

TokenType getType(char *c);

void printToken(Token *token);

void printTokens(TokenList *tokens);

#endif //SIMPLE_INTERPRETER_TOKEN_UTILS_H