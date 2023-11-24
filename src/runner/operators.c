#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "runner/message.h"
#include "runner/operators.h"

VarData evalUnaryOp(const char *op, VarData operand) {
    if (strcmp(op, "!") == 0) {
        return not(operand);
    }

    VarData ret;
    ret.type = VAR_TYPE_ERROR;
    ret.string = ERROR_INVALID_UNARY_OPERATOR;
    return ret;
}

VarData evalBinaryOp(const char *op, VarData lhs, VarData rhs) {
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

    VarData ret;
    ret.type = VAR_TYPE_ERROR;
    ret.string = ERROR_INVALID_BINARY_OPERATOR;
    return ret;
}

VarData not(VarData operand) {
    VarData ret;

    if (operand.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = !operand.number;
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_NOT;
    }

    return ret;
}

VarData add(VarData lhs, VarData rhs) {
    VarData ret;

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

VarData subtract(VarData lhs, VarData rhs) {
    VarData ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = lhs.number - rhs.number;
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_MINUS;
    }

    return ret;
}

VarData multiply(VarData lhs, VarData rhs) {
    VarData ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = lhs.number * rhs.number;
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_MULTIPLY;
    }

    return ret;
}

VarData divide(VarData lhs, VarData rhs) {
    VarData ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = lhs.number / rhs.number;
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_DIVIDE;
    }

    return ret;
}

VarData power(VarData lhs, VarData rhs) {
    VarData ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = pow(lhs.number, rhs.number);
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_POWER;
    }

    return ret;
}

VarData modulo(VarData lhs, VarData rhs) {
    VarData ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = fmod(lhs.number, rhs.number);
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_MODULO;
    }

    return ret;
}

VarData equal(VarData lhs, VarData rhs) {
    VarData ret;

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

VarData notEqual(VarData lhs, VarData rhs) {
    VarData ret;

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

VarData greaterThan(VarData lhs, VarData rhs) {
    VarData ret;

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

VarData lessThan(VarData lhs, VarData rhs) {
    VarData ret;

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

VarData greaterThanOrEqual(VarData lhs, VarData rhs) {
    VarData ret;

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

VarData lessThanOrEqual(VarData lhs, VarData rhs) {
    VarData ret;

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

VarData and(VarData lhs, VarData rhs) {
    VarData ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = lhs.number && rhs.number;
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_AND;
    }

    return ret;
}

VarData or(VarData lhs, VarData rhs) {
    VarData ret;

    if (lhs.type == VAR_TYPE_NUMBER && rhs.type == VAR_TYPE_NUMBER) {
        ret.type = VAR_TYPE_NUMBER;
        ret.number = lhs.number || rhs.number;
    } else {
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_OPERAND_OR;
    }

    return ret;
}
