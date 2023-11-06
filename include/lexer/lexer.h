#ifndef SIMPLE_INTERPRETER_LEXER_H
#define SIMPLE_INTERPRETER_LEXER_H

#include "lexer/token.h"

/*
 * Get the next token from the input string. The current position in the input string is passed as a pointer to an int.
 */
Token nextToken(const char *input, int *current);

/*
 * Tokenize the input string.
 */
TokenList *tokenize(const char *input);

#endif //SIMPLE_INTERPRETER_LEXER_H
