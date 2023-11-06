#ifndef SIMPLE_INTERPRETER_TOKEN_UTILS_H
#define SIMPLE_INTERPRETER_TOKEN_UTILS_H

#include <stdbool.h>

const char *stringifyTokenType(TokenType type);

bool isUnaryOperator(const char *c);

bool isBinaryOperator(const char *c);

bool isRightParen(const char *c);

bool isLeftParen(const char *c);

bool isString(const char *c);

bool isEnd(const char *c);

bool isObject(const char *c);

bool isNumber(const char *c);

bool isBlank(const char *c);

/*
 * Get the TokenType of given string.
 */
TokenType getType(const char *c);

/*
 * Print the given token.
 */
void printToken(const Token *token);

/*
 * Print the given token list.
 */
void printTokens(const TokenList *tokens);

#endif //SIMPLE_INTERPRETER_TOKEN_UTILS_H
