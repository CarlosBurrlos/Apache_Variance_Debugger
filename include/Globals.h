#ifndef INC_408DEBUGGER_GLOBALS_H
#define INC_408DEBUGGER_GLOBALS_H

#include "../include/Scope.h"
#include "../include/Func.h"

#include <unordered_map>
#include <string_view>

extern std::unordered_map<std::string_view, scp *> Scopes;
extern std::unordered_map<std::string_view, func *>  Functions;
extern int Token;

#endif //INC_408DEBUGGER_GLOBALS_H
