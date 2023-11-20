#ifndef SIMPLE_INTERPRETER_OPERATORS_H
#define SIMPLE_INTERPRETER_OPERATORS_H

#include "runner/runtime.h"

ReturnVal evalUnaryOp(const char *op, ReturnVal operand);

ReturnVal evalBinaryOp(const char *op, ReturnVal lhs, ReturnVal rhs);

ReturnVal not(ReturnVal operand);

ReturnVal add(ReturnVal lhs, ReturnVal rhs);

ReturnVal subtract(ReturnVal lhs, ReturnVal rhs);

ReturnVal multiply(ReturnVal lhs, ReturnVal rhs);

ReturnVal divide(ReturnVal lhs, ReturnVal rhs);

ReturnVal power(ReturnVal lhs, ReturnVal rhs);

ReturnVal modulo(ReturnVal lhs, ReturnVal rhs);

ReturnVal equal(ReturnVal lhs, ReturnVal rhs);

ReturnVal notEqual(ReturnVal lhs, ReturnVal rhs);

ReturnVal greaterThan(ReturnVal lhs, ReturnVal rhs);

ReturnVal lessThan(ReturnVal lhs, ReturnVal rhs);

ReturnVal greaterThanOrEqual(ReturnVal lhs, ReturnVal rhs);

ReturnVal lessThanOrEqual(ReturnVal lhs, ReturnVal rhs);

ReturnVal and(ReturnVal lhs, ReturnVal rhs);

ReturnVal or(ReturnVal lhs, ReturnVal rhs);

#endif //SIMPLE_INTERPRETER_OPERATORS_H
