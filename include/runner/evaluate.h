#ifndef SIMPLE_INTERPRETER_EVALUATE_H
#define SIMPLE_INTERPRETER_EVALUATE_H

#include "parser/ast.h"
#include "runner/runtime.h"

/*
 * Evaluate the given AST.
 */
VarData evaluate(ASTNode *ast, Scope *scope);


#endif //SIMPLE_INTERPRETER_EVALUATE_H
