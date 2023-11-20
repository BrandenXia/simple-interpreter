#include <stdlib.h>
#include <string.h>
#include "runner/evaluate.h"
#include "runner/operators.h"

ReturnVal evaluateSTMT(ASTNode *ast, Scope *scope) {
    return evaluate(ast->child->nodes[0], scope);
}

ReturnVal evaluateVAR(ASTNode *ast, Scope *scope) {
    Var *val;

    val = getVar(scope, ast->tokens->tokens[0].value);
    if (val == NULL) {
        ReturnVal ret;
        ret.type = VAR_TYPE_ERROR;
        ret.string = "Variable not found";
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
            val.string = ast->tokens->tokens[0].value;
            break;
        default:
            val.type = VAR_TYPE_ERROR;
            val.string = "Invalid constant type";
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

            if (strcmp(ast->tokens->tokens[0].value, "=") == 0) {
                if (ast->child->nodes[0]->tokens->tokens[0].type != TOKEN_TYPE_OBJECT) {
                    val.type = VAR_TYPE_ERROR;
                    val.string = "Invalid left operand for binary operator";
                    break;
                }

                Var var;
                var.name = ast->child->nodes[0]->tokens->tokens[0].value;
                var.data = right;
                insertVar(scope, var);

                val.type = VAR_TYPE_VOID;
                break;
            }

            if (right.type == VAR_TYPE_ERROR) {
                val.type = VAR_TYPE_ERROR;
                val.string = "Invalid right operand for binary operator";
                break;
            } else if (left.type == VAR_TYPE_ERROR) {
                val.type = VAR_TYPE_ERROR;
                val.string = "Invalid left operand for binary operator";
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
                val.string = "Invalid operand for unary operator";
                break;
            }

            val = evalUnaryOp(ast->tokens->tokens[0].value, operand);

            break;
        }
        default:
            val.type = VAR_TYPE_ERROR;
            val.string = "Invalid operator type";
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
            ret.string = "Invalid AST node type";
            return ret;
        }
    }
}
