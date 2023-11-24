#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "runner/message.h"
#include "runner/operators.h"

ReturnVal evalUnaryOp(const char *op, ReturnVal operand) {
    if (strcmp(op, "!") == 0) {
        return not(operand);
    }

    ReturnVal ret;
    ret.type = VAR_TYPE_ERROR;
    ret.string = ERROR_INVALID_UNARY_OPERATOR;
    return ret;
}

ReturnVal evalBinaryOp(const char *op, ReturnVal lhs, ReturnVal rhs) {
    if (strcmp(op, "+") == 0) {
        return add(lhs, rhs);
    } else if (strcmp(op, "-") == 0) {
        return subtract(lhs, rhs);
    } else if (strcmp(op, "*") == 0) {
        return multiply(lhs, rhs);
    } else if (strcmp(op, "/") == 0) {
        return divide(lhs, rhs);
    } else if (strcmp(op, "^") == 0) {
        return power(lhs, rhs);
    } else if (strcmp(op, "%") == 0) {
        return modulo(lhs, rhs);
    } else if (strcmp(op, "==") == 0) {
        return equal(lhs, rhs);
    } else if (strcmp(op, "!=") == 0) {
        return notEqual(lhs, rhs);
    } else if (strcmp(op, ">") == 0) {
        return greaterThan(lhs, rhs);
    } else if (strcmp(op, "<") == 0) {
        return lessThan(lhs, rhs);
    } else if (strcmp(op, ">=") == 0) {
        return greaterThanOrEqual(lhs, rhs);
    } else if (strcmp(op, "<=") == 0) {
        return lessThanOrEqual(lhs, rhs);
    } else if (strcmp(op, "&&") == 0) {
        return and(lhs, rhs);
    } else if (strcmp(op, "||") == 0) {
        return or(lhs, rhs);
    }

    ReturnVal ret;
    ret.type = VAR_TYPE_ERROR;
    ret.string = ERROR_INVALID_BINARY_OPERATOR;
    return ret;
}

ReturnVal not(ReturnVal operand) {
    ReturnVal ret;

    if (operand.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = !operand.number;
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_NOT;
    }

    return ret;
}

ReturnVal add(ReturnVal lhs, ReturnVal rhs) {
    ReturnVal ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = lhs.number + rhs.number;
    } else if (lhs.type == VAR_TYPE_STRING && rhs.type == VAR_TYPE_STRING) {
        ret.type = VAR_TYPE_STRING;
        ret.string = malloc(strlen(lhs.string) + strlen(rhs.string) + 1);
        strcpy(ret.string, lhs.string);
        strcat(ret.string, rhs.string);
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_PLUS;
    }

    return ret;
}

ReturnVal subtract(ReturnVal lhs, ReturnVal rhs) {
    ReturnVal ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = lhs.number - rhs.number;
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_MINUS;
    }

    return ret;
}

ReturnVal multiply(ReturnVal lhs, ReturnVal rhs) {
    ReturnVal ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = lhs.number * rhs.number;
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_MULTIPLY;
    }

    return ret;
}

ReturnVal divide(ReturnVal lhs, ReturnVal rhs) {
    ReturnVal ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = lhs.number / rhs.number;
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_DIVIDE;
    }

    return ret;
}

ReturnVal power(ReturnVal lhs, ReturnVal rhs) {
    ReturnVal ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = pow(lhs.number, rhs.number);
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_POWER;
    }

    return ret;
}

ReturnVal modulo(ReturnVal lhs, ReturnVal rhs) {
    ReturnVal ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = fmod(lhs.number, rhs.number);
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_MODULO;
    }

    return ret;
}

ReturnVal equal(ReturnVal lhs, ReturnVal rhs) {
    ReturnVal ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = lhs.number == rhs.number;
    } else if (lhs.type == VAR_TYPE_STRING && rhs.type == VAR_TYPE_STRING) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = strcmp(lhs.string, rhs.string) == 0;
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_EQUAL;
    }

    return ret;
}

ReturnVal notEqual(ReturnVal lhs, ReturnVal rhs) {
    ReturnVal ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = lhs.number != rhs.number;
    } else if (lhs.type == VAR_TYPE_STRING && rhs.type == VAR_TYPE_STRING) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = strcmp(lhs.string, rhs.string) != 0;
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_NOT_EQUAL;
    }

    return ret;
}

ReturnVal greaterThan(ReturnVal lhs, ReturnVal rhs) {
    ReturnVal ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = lhs.number > rhs.number;
    } else if (lhs.type == VAR_TYPE_STRING && rhs.type == VAR_TYPE_STRING) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = strcmp(lhs.string, rhs.string) > 0;
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_GREATER_THAN;
    }

    return ret;
}

ReturnVal lessThan(ReturnVal lhs, ReturnVal rhs) {
    ReturnVal ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = lhs.number < rhs.number;
    } else if (lhs.type == VAR_TYPE_STRING && rhs.type == VAR_TYPE_STRING) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = strcmp(lhs.string, rhs.string) < 0;
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_LESS_THAN;
    }

    return ret;
}

ReturnVal greaterThanOrEqual(ReturnVal lhs, ReturnVal rhs) {
    ReturnVal ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = lhs.number >= rhs.number;
    } else if (lhs.type == VAR_TYPE_STRING && rhs.type == VAR_TYPE_STRING) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = strcmp(lhs.string, rhs.string) >= 0;
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_GREATER_THAN_OR_EQUAL;
    }

    return ret;
}

ReturnVal lessThanOrEqual(ReturnVal lhs, ReturnVal rhs) {
    ReturnVal ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = lhs.number <= rhs.number;
    } else if (lhs.type == VAR_TYPE_STRING && rhs.type == VAR_TYPE_STRING) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = strcmp(lhs.string, rhs.string) <= 0;
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_LESS_THAN_OR_EQUAL;
    }

    return ret;
}

ReturnVal and(ReturnVal lhs, ReturnVal rhs) {
    ReturnVal ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = lhs.number && rhs.number;
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_AND;
    }

    return ret;
}

ReturnVal or(ReturnVal lhs, ReturnVal rhs) {
    ReturnVal ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = lhs.number || rhs.number;
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_OR;
    }

    return ret;
}
