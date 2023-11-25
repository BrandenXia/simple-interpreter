#ifndef SIMPLE_INTERPRETER_VAR_HASH_MAP_H
#define SIMPLE_INTERPRETER_VAR_HASH_MAP_H

#include "var.h"

#define VAR_HASH_MAP_INITIAL_CAPACITY 16
#define VAR_HASH_MAP_MAX_LOAD_FACTOR 0.75
#define VAR_HASH_MAP_EXPANSION_FACTOR 2

typedef struct Entry {
    char *name;
    VarData data;
    struct Entry *next;
} Entry;

typedef struct {
    Entry *table;
    int size;
    int capacity;
} VarHashMap;

void initializeVarHashMap(VarHashMap **dst);

void freeVarHashMap(VarHashMap *map);

void insertVar(VarHashMap *map, char *name, VarData data);

VarData *getVar(VarHashMap *map, const char *name);

#endif //SIMPLE_INTERPRETER_VAR_HASH_MAP_H
