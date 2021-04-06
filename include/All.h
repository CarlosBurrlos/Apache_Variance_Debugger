#ifndef INC_408DEBUGGER_ALL_H
#define INC_408DEBUGGER_ALL_H

#define ENDWORD     -2
#define OK           1
#define STARTWORD    2
#define END          3

#include    "Invar.h"
#include    "Globals.h"
#include    "Debugger.h"
#include    "Func.h"
#include    "NFAs.h"
#include    "Parser.h"
#include    "Scanner.h"
#include    "Scope.h"

extern std::unordered_map<std::string_view, scp *> Scopes;
extern std::unordered_map<std::string_view, func *>  Functions;
#endif //INC_408DEBUGGER_ALL_H
