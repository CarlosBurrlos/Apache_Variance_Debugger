#ifndef INC_408DEBUGGER_GLOBALS_H
#define INC_408DEBUGGER_GLOBALS_H

#include <unordered_map>
#include <string_view>
#include "Invar.h"

extern int Token;
extern std::unordered_map<std::string_view/*scpName*/, Scope *> allScopes;
extern std::unordered_map<std::string_view/*Name*/,Func *> allFuncs;
extern std::unordered_map<size_t, Invar *> Invars;

#endif //INC_408DEBUGGER_GLOBALS_H
