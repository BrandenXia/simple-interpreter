#include <stdlib.h>
#include <string.h>
#include "runner/var_hash_map.h"

unsigned int BKDRHash(const char *str) {
    unsigned int seed = 131;
    unsigned int hash = 0;

    while (*str) {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

unsigned int hash(unsigned int hash) {
    return hash ^ (hash >> 16);
}

unsigned int indexFor(unsigned int hash, unsigned int capacity) {
    return hash & (capacity - 1);
}

void initializeVarHashMap(VarHashMap **dst) {
    VarHashMap *map;

    map = malloc(sizeof(VarHashMap));
    map->vars = malloc(sizeof(Var) * VAR_HASH_MAP_INITIAL_CAPACITY);
    map->size = 0;
    map->capacity = VAR_HASH_MAP_INITIAL_CAPACITY;

    // Initialize the variables
    for (int i = 0; i < map->capacity; i++) {
        map->vars[i].name = NULL;
    }

    *dst = map;
}

void freeVarHashMap(VarHashMap *map) {
    for (int i = 0; i < map->size; i++) {
        free(map->vars[i].name);
        if (map->vars[i].data.type == VAR_TYPE_STRING) free(map->vars[i].data.string);
    }

    free(map->vars);
    free(map);
}

void insertVar(VarHashMap *map, Var var) {
    unsigned int h;
    unsigned int index;

    if (map->size > map->capacity * 0.75) {
        map->capacity *= 2;
        Var *newVars = malloc(sizeof(Var) * map->capacity);
        if (newVars == NULL) exit(1);

        for (int i = 0; i < map->size; i++) {
            h = hash(BKDRHash(map->vars[i].name));
            index = indexFor(h, map->capacity);
            newVars[index] = map->vars[i];
        }

        free(map->vars);
        map->vars = newVars;
    }

    h = hash(BKDRHash(var.name));
    index = indexFor(h, map->capacity);

    map->vars[index] = var;
    map->size++;
}


Var *getVar(VarHashMap *map, const char *name) {
    unsigned int h = hash(BKDRHash(name));
    unsigned int index = indexFor(h, map->capacity);

    // Check if the variable is found
    if (map->vars[index].name != NULL && strcmp(map->vars[index].name, name) == 0) {
        return &map->vars[index];
    }

    return NULL; // Variable not found
}
