#ifndef INC_408DEBUGGER_GLOBALS_H
#define INC_408DEBUGGER_GLOBALS_H

#include <unordered_map>
#include <string_view>

typedef struct S scp;
typedef struct F func;

typedef struct S {
    std::string_view name;
    std::unordered_map<std::string_view, func *> Funcs;
}scp;

typedef struct F {
    int nCalls;
    std::string_view name;
    std::unordered_map<std::string_view, int> pairs;
}func;



extern int Token;
#endif //INC_408DEBUGGER_GLOBALS_H
