#ifndef SIMPLE_INTERPRETER_RUNNER_H
#define SIMPLE_INTERPRETER_RUNNER_H

#include "parser/ast.h"
#include "runner/runtime.h"

/*
 * Run the given AST.
 */
void runAST(ASTNode *ast, Scope *scope);

#endif //SIMPLE_INTERPRETER_RUNNER_H
