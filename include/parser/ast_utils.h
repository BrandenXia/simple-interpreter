#ifndef SIMPLE_INTERPRETER_AST_UTILS_H
#define SIMPLE_INTERPRETER_AST_UTILS_H

#include "ast.h"

const char *stringifyASTNodeTypes(ASTNodeType type);

void printAST(ASTNode *root, int level);

#endif //SIMPLE_INTERPRETER_AST_UTILS_H
