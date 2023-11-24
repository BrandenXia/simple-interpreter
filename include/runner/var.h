#ifndef SIMPLE_INTERPRETER_VAR_H
#define SIMPLE_INTERPRETER_VAR_H

typedef enum {
    VAR_TYPE_NUMBER,
    VAR_TYPE_STRING,
    VAR_TYPE_VOID,
    VAR_TYPE_ERROR
} VarType;

typedef struct {
    VarType type;
    union {
        double number;
        char *string;
        char *error;
    };
} VarData;

typedef struct {
    char *name;
    VarData data;
} Var;

#endif //SIMPLE_INTERPRETER_VAR_H
