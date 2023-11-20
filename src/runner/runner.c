#include <stdio.h>
#include "runner/runner.h"
#include "runner/evaluate.h"

void runAST(ASTNode *ast, Scope *scope) {
    if (ast->type != AST_NODE_TYPE_PROGRAM) return;

    for (int i = 0; i < ast->child->size; i++) {
        ReturnVal val;

        val = evaluate(ast->child->nodes[i], scope);

        switch (val.type) {
            case VAR_TYPE_NUMBER:
                printf("%f\n", val.number);
                break;
            case VAR_TYPE_STRING:
                printf("%s\n", val.string);
                break;
            case VAR_TYPE_ERROR:
                printf("Error: %s\n", val.string);
                break;
            default:
                break;
        }
    }
}
