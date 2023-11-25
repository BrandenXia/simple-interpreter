#ifndef SIMPLE_INTERPRETER_VAR_HASH_MAP_H
#define SIMPLE_INTERPRETER_VAR_HASH_MAP_H

#include "var.h"

#define VAR_HASH_MAP_INITIAL_CAPACITY 16

typedef struct {
    Var *vars;
    int size;
    int capacity;
} VarHashMap;

void initializeVarHashMap(VarHashMap **dst);

void freeVarHashMap(VarHashMap *map);

void insertVar(VarHashMap *map, Var var);

Var *getVar(VarHashMap *map, const char *name);

#endif //SIMPLE_INTERPRETER_VAR_HASH_MAP_H
