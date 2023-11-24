#ifndef SIMPLE_INTERPRETER_OPERATORS_H
#define SIMPLE_INTERPRETER_OPERATORS_H

#include "runner/runtime.h"

VarData evalUnaryOp(const char *op, VarData operand);

VarData evalBinaryOp(const char *op, VarData lhs, VarData rhs);

VarData not(VarData operand);

VarData add(VarData lhs, VarData rhs);

VarData subtract(VarData lhs, VarData rhs);

VarData multiply(VarData lhs, VarData rhs);

VarData divide(VarData lhs, VarData rhs);

VarData power(VarData lhs, VarData rhs);

VarData modulo(VarData lhs, VarData rhs);

VarData equal(VarData lhs, VarData rhs);

VarData notEqual(VarData lhs, VarData rhs);

VarData greaterThan(VarData lhs, VarData rhs);

VarData lessThan(VarData lhs, VarData rhs);

VarData greaterThanOrEqual(VarData lhs, VarData rhs);

VarData lessThanOrEqual(VarData lhs, VarData rhs);

VarData and(VarData lhs, VarData rhs);

VarData or(VarData lhs, VarData rhs);

#endif //SIMPLE_INTERPRETER_OPERATORS_H
