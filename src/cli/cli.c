#include <unistd.h>
#include <stdlib.h>
#include "cli/cli.h"

const char *VERSION = "0.1.0";

void parseArgs(CLI **dst, int argc, char **argv) {
    CLI *cli;
    int opt;

    cli = malloc(sizeof(CLI));
    cli->mode = INTERACTIVE_MODE;

    while ((opt = getopt(argc, argv, "f:htavV")) != -1) {
        switch (opt) {
            case 'f':
                cli->mode = FILE_MODE;
                cli->file = optarg;
                break;
            case 't':
                cli->flags[TOKEN_FLAG] = true;
                break;
            case 'a':
                cli->flags[AST_FLAG] = true;
                break;
            case 'v':
                cli->flags[VERBOSE_FLAG] = true;
                break;
            case 'V':
                cli->flags[VERSION_FLAG] = true;
                break;
            case 'h':
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
    printf("Usage: simple-interpreter [options]\n");
    printf("Modes:\n");
    printf("  [no option]  Interactive mode\n");
    printf("  -f <file>    File mode\n");
    printf("Options:\n");
    printf("  -t           Print tokens\n");
    printf("  -a           Print AST\n");
    printf("  -v           Verbose mode\n");
    printf("  -h           Print help and exit\n");
    printf("  -V           Print version and exit\n");
}

void printVersion(void) {
    printf("simple-interpreter v%s\n", VERSION);
}
