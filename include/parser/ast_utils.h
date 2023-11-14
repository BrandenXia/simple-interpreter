#ifndef SIMPLE_INTERPRETER_AST_UTILS_H
#define SIMPLE_INTERPRETER_AST_UTILS_H

#include "ast.h"

const char *stringifyASTNodeTypes(ASTNodeType type);

int getPrecedence(const char *op);

void printAST(const ASTNode *root, int level);

#endif //SIMPLE_INTERPRETER_AST_UTILS_H
