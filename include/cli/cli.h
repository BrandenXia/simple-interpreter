#ifndef SIMPLE_INTERPRETER_CLI_H
#define SIMPLE_INTERPRETER_CLI_H

#include <stdio.h>
#include <stdbool.h>

#define VERSION "0.1.0"

typedef enum {
    FILE_MODE,
    INTERACTIVE_MODE
} RunMode;

typedef enum {
    HELP_FLAG,
    VERSION_FLAG,
    TOKEN_FLAG,
    AST_FLAG,
    VERBOSE_FLAG
} Flag;

typedef struct {
    RunMode mode;
    bool flags[5];
    char *file;
} CLI;

/*
 * Parse CLI arguments.
 */
void parseArgs(CLI **dst, int argc, char **argv);

/*
 * Print help message.
 */
void printHelp(void);

/*
 * Print version.
 */
void printVersion(void);

#endif //SIMPLE_INTERPRETER_CLI_H
