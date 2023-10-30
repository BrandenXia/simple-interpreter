#ifndef SIMPLE_INTERPRETER_PARSER_H
#define SIMPLE_INTERPRETER_PARSER_H

#include "parser/ast.h"
#include "lexer/token.h"

ASTNode *parse(const TokenList *tokens);

ASTNode *parseStatements(const TokenList *tokens);

#endif //SIMPLE_INTERPRETER_PARSER_H