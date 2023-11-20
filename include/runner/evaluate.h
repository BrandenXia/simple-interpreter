#ifndef SIMPLE_INTERPRETER_EVALUATE_H
#define SIMPLE_INTERPRETER_EVALUATE_H

#include "parser/ast.h"
#include "runner/runtime.h"

ReturnVal evaluateSTMT(ASTNode *ast, Scope *scope);

ReturnVal evaluateVAR(ASTNode *ast, Scope *scope);

inline ReturnVal evaluateCONST(ASTNode *ast);

ReturnVal evaluateOP(ASTNode *ast, Scope *scope);

/*
 * Evaluate the given AST.
 */
ReturnVal evaluate(ASTNode *ast, Scope *scope);


#endif //SIMPLE_INTERPRETER_EVALUATE_H
