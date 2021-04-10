#ifndef INC_408DEBUGGER_SCOPE_H
#define INC_408DEBUGGER_SCOPE_H
#include "../include/Func.h"

#include <string_view>

typedef struct S {
    std::string_view name;
    std::unordered_map<std::string_view, func *> Funcs;
}scp;

scp * newScope(std::string_view);
int     addFunc(scp *, func *);
bool    find(scp *, std::string_view);
#endif //INC_408DEBUGGER_SCOPE_H
