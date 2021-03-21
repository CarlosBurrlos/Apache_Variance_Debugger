#ifndef INC_408DEBUGGER_GLOBALS_H
#define INC_408DEBUGGER_GLOBALS_H

extern int Token;
extern std::unordered_map<std::string_view/*scpName*/, Scope *> allScopes;
extern std::unordered_map<std::string_view/*Name*/,Func *> allFuncs;

#endif //INC_408DEBUGGER_GLOBALS_H
