#ifndef SIMPLE_INTERPRETER_LEXER_H
#define SIMPLE_INTERPRETER_LEXER_H

#include <stdio.h>
#include "lexer/token.h"

/*
 * Tokenize the input file and store the tokens in the token list.
 * This function allocates memory for the token list, so the caller is responsible for freeing it.
 */
void tokenize(TokenStack **dst, FILE *input);

#endif //SIMPLE_INTERPRETER_LEXER_H
