#include <stdlib.h>
#include <string.h>
#include "runner/evaluate.h"
#include "runner/message.h"
#include "runner/operators.h"

ReturnVal evaluateSTMT(ASTNode *ast, Scope *scope) {
    if (ast->child->size > 0) {
        return evaluate(ast->child->nodes[0], scope);
    } else {
        ReturnVal ret;
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_INVALID_STATEMENT;
        return ret;
    }
}

ReturnVal evaluateVAR(ASTNode *ast, Scope *scope) {
    Var *val;

    val = getVar(scope, ast->tokens->tokens[0].value);
    if (val == NULL) {
        ReturnVal ret;
        ret.type = VAR_TYPE_ERROR;
        ret.error = ERROR_VARIABLE_NOT_FOUND;
        return ret;
    }

    return val->data;
}

inline ReturnVal evaluateCONST(ASTNode *ast) {
    ReturnVal val;

    switch (ast->tokens->tokens[0].type) {
        case TOKEN_TYPE_NUMBER:
            val.type = VAR_TYPE_NUMBER;
            val.number = strtod(ast->tokens->tokens[0].value, NULL);
            break;
        case TOKEN_TYPE_STRING:
            val.type = VAR_TYPE_STRING;
            val.string = calloc(strlen(ast->tokens->tokens[0].value) - 1, sizeof(char));
            val.string = strncpy(val.string, ast->tokens->tokens[0].value + 1, strlen(ast->tokens->tokens[0].value) - 2);
            break;
        default:
            val.type = VAR_TYPE_ERROR;
            val.error = ERROR_INVALID_CONSTANT_TYPE;
            break;
    }

    return val;
}

ReturnVal evaluateOP(ASTNode *ast, Scope *scope) {
    ReturnVal val;

    switch (ast->tokens->tokens[0].type) {
        case TOKEN_TYPE_BINARY_OPERATOR: {
            ReturnVal left, right;

            left = evaluate(ast->child->nodes[0], scope);
            right = evaluate(ast->child->nodes[1], scope);

            if (right.type == VAR_TYPE_ERROR) {
                val.type = VAR_TYPE_ERROR;
                val.error = ERROR_INVALID_RIGHT_OPERAND;
                break;
            }

            if (strcmp(ast->tokens->tokens[0].value, "=") == 0) {
                if (ast->child->nodes[0]->tokens->tokens[0].type != TOKEN_TYPE_OBJECT) {
                    val.type = VAR_TYPE_ERROR;
                    val.error = ERROR_INVALID_LEFT_OPERAND;
                    break;
                }

                Var var;
                var.name = ast->child->nodes[0]->tokens->tokens[0].value;
                var.data = right;
                insertVar(scope, var);

                val.type = VAR_TYPE_VOID;
                break;
            }

            if (left.type == VAR_TYPE_ERROR) {
                val.type = VAR_TYPE_ERROR;
                val.error = ERROR_INVALID_LEFT_OPERAND;
                break;
            }

            val = evalBinaryOp(ast->tokens->tokens[0].value, left, right);

            break;
        }
        case TOKEN_TYPE_UNARY_OPERATOR: {
            ReturnVal operand;

            operand = evaluate(ast->child->nodes[0], scope);

            if (operand.type == VAR_TYPE_ERROR) {
                val.type = VAR_TYPE_ERROR;
                val.error = ERROR_INVALID_OPERAND;
                break;
            }

            val = evalUnaryOp(ast->tokens->tokens[0].value, operand);

            break;
        }
        default:
            val.type = VAR_TYPE_ERROR;
            val.error = ERROR_INVALID_OPERATOR;
            break;
    }

    return val;
}

ReturnVal evaluate(ASTNode *ast, Scope *scope) {
    switch (ast->type) {
        case AST_NODE_TYPE_STMT:
            return evaluateSTMT(ast, scope);
        case AST_NODE_TYPE_VAR:
            return evaluateVAR(ast, scope);
        case AST_NODE_TYPE_CONST:
            return evaluateCONST(ast);
        case AST_NODE_TYPE_OP:
            return evaluateOP(ast, scope);
        default: {
            ReturnVal ret;
            ret.type = VAR_TYPE_ERROR;
            ret.error = ERROR_INVALID_AST_NODE;
            return ret;
        }
    }
}
