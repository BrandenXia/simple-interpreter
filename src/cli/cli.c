#include <unistd.h>
#include <stdlib.h>
#include "cli/cli.h"

void parseArgs(CLI **dst, int argc, char **argv) {
    CLI *cli;
    int opt;

    cli = malloc(sizeof(CLI));
    cli->mode = INTERACTIVE_MODE;

    while ((opt = getopt(argc, argv, OPT_STR)) != -1) {
        switch (opt) {
            case FILE_FLAG_OPT:
                cli->mode = FILE_MODE;
                cli->file = optarg;
                break;
            case TOKEN_FLAG_OPT:
                cli->flags[TOKEN_FLAG] = true;
                break;
            case AST_FLAG_OPT:
                cli->flags[AST_FLAG] = true;
                break;
            case VERBOSE_FLAG_OPT:
                cli->flags[VERBOSE_FLAG] = true;
                break;
            case VERSION_FLAG_OPT:
                cli->flags[VERSION_FLAG] = true;
                break;
            case HELP_FLAG_OPT:
                cli->flags[HELP_FLAG] = true;
                break;
            case '?':
                fprintf(stderr, "Unknown option: %c\n", optopt);
                cli->flags[HELP_FLAG] = true;
                break;
            default:
                break;
        }
    }

    *dst = cli;
}

void printHelp(void) {
    printf(HELP_MSG);
}

void printVersion(void) {
    printf("simple-interpreter v%s\n", VERSION);
}
