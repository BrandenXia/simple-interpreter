#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "runner/evaluate.h"
#include "runner/message.h"
#include "runner/operators.h"

#define format_assign_message(var, format, content) \
    var = malloc(sizeof(format) + strlen(content) * sizeof(char) - 2 * sizeof(char)); \
    sprintf(var, format, content)

VarData evaluateSTMT(ASTNode *ast, Scope *scope) {
    if (ast->child->size > 0) {
        return evaluate(ast->child->nodes[0], scope);
    }

    VarData ret;
    ret.type = VAR_TYPE_ERROR;
    ret.error = ERROR_INVALID_STATEMENT;
    return ret;
}

VarData evaluateVAR(ASTNode *ast, Scope *scope) {
    VarData *val;

    val = getVar(scope, ast->tokens->tokens[0].value);
    if (val == NULL) {
        VarData ret;
        ret.type = VAR_TYPE_ERROR;
        format_assign_message(ret.error, ERROR_VARIABLE_NOT_FOUND, ast->tokens->tokens[0].value);
        return ret;
    }

    return *val;
}

inline VarData evaluateCONST(ASTNode *ast) {
    VarData val;

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

VarData evaluateOP(ASTNode *ast, Scope *scope) {
    VarData val;

    switch (ast->tokens->tokens[0].type) {
        case TOKEN_TYPE_BINARY_OPERATOR: {
            VarData left, right;

            left = evaluate(ast->child->nodes[0], scope);
            right = evaluate(ast->child->nodes[1], scope);

            if (right.type == VAR_TYPE_ERROR) {
                val.type = VAR_TYPE_ERROR;
                format_assign_message(val.error, ERROR_INVALID_RIGHT_OPERAND, right.error);
                break;
            }

            if (strcmp(ast->tokens->tokens[0].value, "=") == 0) {
                if (ast->child->nodes[0]->tokens->tokens[0].type != TOKEN_TYPE_OBJECT) {
                    val.type = VAR_TYPE_ERROR;
                    format_assign_message(val.error, ERROR_INVALID_LEFT_OPERAND, ast->child->nodes[0]->tokens->tokens[0].value);
                    break;
                }

                insertVar(scope, ast->child->nodes[0]->tokens->tokens[0].value, right);

                val.type = VAR_TYPE_VOID;
                break;
            }

            if (left.type == VAR_TYPE_ERROR) {
                val.type = VAR_TYPE_ERROR;
                format_assign_message(val.error, ERROR_INVALID_LEFT_OPERAND, left.error);
                break;
            }

            val = evalBinaryOp(ast->tokens->tokens[0].value, left, right);

            break;
        }
        case TOKEN_TYPE_UNARY_OPERATOR: {
            VarData operand;

            operand = evaluate(ast->child->nodes[0], scope);

            if (operand.type == VAR_TYPE_ERROR) {
                val.type = VAR_TYPE_ERROR;
                format_assign_message(val.error, ERROR_INVALID_OPERAND, operand.error);
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

VarData evaluate(ASTNode *ast, Scope *scope) {
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
            VarData ret;
            ret.type = VAR_TYPE_ERROR;
            ret.error = ERROR_INVALID_AST_NODE;
            return ret;
        }
    }
}
