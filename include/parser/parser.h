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
 * Parse an expression node.
 */
void parseExpression(ASTNode *ast);

#endif //SIMPLE_INTERPRETER_PARSER_H
