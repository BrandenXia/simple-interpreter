#ifndef SIMPLE_INTERPRETER_LEXER_H
#define SIMPLE_INTERPRETER_LEXER_H

#include "lexer/token.h"

Token nextToken(const char *input, int *current);

TokenList *tokenize(const char *input);

#endif //SIMPLE_INTERPRETER_LEXER_H
