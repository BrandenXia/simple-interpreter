#ifndef SIMPLE_INTERPRETER_EVALUATE_H
#define SIMPLE_INTERPRETER_EVALUATE_H

#include "parser/ast.h"
#include "runner/runtime.h"

VarData evaluateSTMT(ASTNode *ast, Scope *scope);

VarData evaluateVAR(ASTNode *ast, Scope *scope);

VarData evaluateCONST(ASTNode *ast);

VarData evaluateOP(ASTNode *ast, Scope *scope);

/*
 * Evaluate the given AST.
 */
VarData evaluate(ASTNode *ast, Scope *scope);


#endif //SIMPLE_INTERPRETER_EVALUATE_H
