#ifndef SIMPLE_INTERPRETER_RUNTIME_H
#define SIMPLE_INTERPRETER_RUNTIME_H

#include "runner/var_hash_map.h"

typedef VarHashMap Scope;

#define initScope(dst) initializeVarHashMap(dst)

#define freeScope(scope) freeVarHashMap(scope)

#endif //SIMPLE_INTERPRETER_RUNTIME_H
