#ifndef SIMPLE_INTERPRETER_CLI_H
#define SIMPLE_INTERPRETER_CLI_H

#include <stdio.h>
#include <stdbool.h>

#define OPT_STR "f:htavV"
#define FILE_FLAG_OPT 'f'
#define TOKEN_FLAG_OPT 't'
#define AST_FLAG_OPT 'a'
#define VERBOSE_FLAG_OPT 'v'
#define VERSION_FLAG_OPT 'V'
#define HELP_FLAG_OPT 'h'

#define HELP_MSG "Usage: simple-interpreter [options]\n" \
                 "Modes:\n" \
                 "  [no option]  Interactive mode\n" \
                 "  -f <file>    File mode\n" \
                 "Options:\n" \
                 "  -t           Print tokens\n" \
                 "  -a           Print AST\n" \
                 "  -v           Verbose mode\n" \
                 "  -h           Print help and exit\n" \
                 "  -V           Print version and exit\n"

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
