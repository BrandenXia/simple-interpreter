#ifndef SIMPLE_INTERPRETER_TOKEN_UTILS_H
#define SIMPLE_INTERPRETER_TOKEN_UTILS_H

#include <stdbool.h>
#include "lexer/token.h"

const char *stringifyTokenType(TokenType type);

/*
 * Get the TokenType of given string.
 */
TokenType getType(const char *c);

/*
 * Print the given token list.
 */
void printTokens(const TokenStack *tokens);

#endif //SIMPLE_INTERPRETER_TOKEN_UTILS_H
