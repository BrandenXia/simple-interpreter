#ifndef SIMPLE_INTERPRETER_PARSER_H
#define SIMPLE_INTERPRETER_PARSER_H

#include "parser/ast.h"

/*
 * Parse a token list into an AST.
 */
void parse(ASTNode **dst, TokenList *tokens);

/*
 * Parse a program node.
 */
void parseProgram(ASTNode *ast);

/*
 * Parse a statement node.
 */
void parseStatement(ASTNode *ast);

/*
 * Convert a token stack into a postfix token stack.
 * This function will allocate memory for the dst, so the caller is responsible for freeing it.
 */
void shuntingYard(TokenStack **dst, TokenStack *tokens);

#endif //SIMPLE_INTERPRETER_PARSER_H
