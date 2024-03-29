#ifndef SIMPLE_INTERPRETER_VAR_H
#define SIMPLE_INTERPRETER_VAR_H

#include <stdbool.h>

typedef enum {
    VAR_TYPE_NUMBER,
    VAR_TYPE_STRING,
    VAR_TYPE_BOOL,
    VAR_TYPE_VOID,
    VAR_TYPE_ERROR
} VarType;

typedef struct {
    VarType type;
    union {
        double number;
        char *string;
        bool boolean;
        char *error;
    };
} VarData;

#endif //SIMPLE_INTERPRETER_VAR_H
