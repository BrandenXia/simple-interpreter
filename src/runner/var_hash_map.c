#include <stdlib.h>
#include <string.h>
#include "runner/var_hash_map.h"

inline unsigned int hash(const char *str) {
    // djb2 hash function
    unsigned int hash = 5381;
    int c;
    while ((c = (unsigned char) *str++)) {
        hash = ((hash << 5u) + hash) + c;
    }
    return hash;
}

inline unsigned int getKey(const char *str, int capacity) {
    return hash(str) % capacity;
}

void rehash(VarHashMap *map) {
    int oldCapacity = map->capacity;
    Entry *oldTable = map->table;
    map->capacity *= VAR_HASH_MAP_EXPANSION_FACTOR;
    map->table = calloc((size_t) map->capacity, sizeof(Entry));
    for (int i = 0; i < oldCapacity; i++) {
        Entry *entry = oldTable[i].next;
        while (entry != NULL) {
            Entry *next = entry->next;
            insertVar(map, entry->name, entry->data);
            free(entry);
            entry = next;
        }
    }
    free(oldTable);
}

void initializeVarHashMap(VarHashMap **dst) {
    *dst = malloc(sizeof(VarHashMap));
    (*dst)->size = 0;
    (*dst)->capacity = VAR_HASH_MAP_INITIAL_CAPACITY;
    (*dst)->table = calloc((size_t) (*dst)->capacity, sizeof(Entry));
}

void freeVarHashMap(VarHashMap *map) {
    for (int i = 0; i < map->capacity; i++) {
        Entry *entry = map->table[i].next;
        while (entry != NULL) {
            Entry *next = entry->next;
            free(entry->name);
            if (entry->data.type == VAR_TYPE_STRING || entry->data.type == VAR_TYPE_ERROR) {
                free(entry->data.string);
            }
            free(entry);
            entry = next;
        }
    }
    free(map->table);
    free(map);
}

void insertVar(VarHashMap *map, char *name, VarData data) {
    if (map->size >= map->capacity * VAR_HASH_MAP_MAX_LOAD_FACTOR) {
        rehash(map);
    }
    unsigned int key = getKey(name, map->capacity);
    Entry *entry = &map->table[key];
    while (entry->next != NULL) {
        entry = entry->next;
    }
    entry->next = malloc(sizeof(Entry));
    entry->next->name = name;
    entry->next->data = data;
    entry->next->next = NULL;
    map->size++;
}

VarData *getVar(VarHashMap *map, const char *name) {
    unsigned int key = getKey(name, map->capacity);
    Entry *entry = map->table[key].next;
    while (entry != NULL) {
        if (strcmp(entry->name, name) == 0) {
            return &entry->data;
        }
        entry = entry->next;
    }
    return NULL;
}
