#include <string.h>
#include "cli/cli.h"
#include "lexer/lexer.h"
#include "lexer/token_utils.h"
#include "parser/parser.h"
#include "parser/ast_utils.h"
#include "runner/runner.h"

void run(FILE *input, bool tokenFlag, bool astFlag, bool verboseFlag, Scope *scope) {
    TokenStack *tokens;
    ASTNode *root;

    tokenize(&tokens, input);

    if (tokenFlag || verboseFlag) {
        printTokens(tokens);
    }

    parse(&root, tokens);

    if (astFlag || verboseFlag) {
        printAST(root, 0);
    }

    runAST(root, scope);

    freeASTNode(root);
}

int main(int argc, char *argv[]) {
    CLI *cli;
    Scope *scope;

    parseArgs(&cli, argc, argv);

    if (cli->flags[HELP_FLAG]) {
        printHelp();
        return 0;
    }

    if (cli->flags[VERSION_FLAG]) {
        printVersion();
        return 0;
    }

    initScope(&scope);

    if (cli->mode == FILE_MODE) {
        FILE *input;

        input = fopen(cli->file, "r");

        if (input == NULL) {
            fprintf(stderr, "Error: could not open file %s\n", cli->file);
            return 1;
        }

        run(input, cli->flags[TOKEN_FLAG], cli->flags[AST_FLAG], cli->flags[VERBOSE_FLAG], scope);
    }

    char *line = NULL;
    size_t len = 0;

    if (cli->mode == INTERACTIVE_MODE) {
        printVersion();
        printf("Type 'exit' to exit.\n");
        printf(">>> ");

        while (getline(&line, &len, stdin) != -1) {
            if (strcmp(line, "exit\n") == 0) break;

            run(fmemopen(line, strlen(line), "r"), cli->flags[TOKEN_FLAG], cli->flags[AST_FLAG],
                   cli->flags[VERBOSE_FLAG], scope);

            printf(">>> ");
        }
    }

    freeScope(scope);
}
