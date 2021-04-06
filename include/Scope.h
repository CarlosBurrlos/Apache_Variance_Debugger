#ifndef INC_408DEBUGGER_SCOPE_H
#define INC_408DEBUGGER_SCOPE_H


#include <string_view>
#include "Globals.h"

scp * newScope(std::string_view);
int     addFunc(scp *, func *);
bool    find(scp *, std::string_view);
#endif //INC_408DEBUGGER_SCOPE_H
