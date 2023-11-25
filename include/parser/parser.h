#ifndef SIMPLE_INTERPRETER_PARSER_H
#define SIMPLE_INTERPRETER_PARSER_H

#include "parser/ast.h"

/*
 * Parse a token list into an AST.
 */
void parse(ASTNode **dst, TokenStack *tokens);

#endif //SIMPLE_INTERPRETER_PARSER_H
