#ifndef INC_408DEBUGGER_FUNC_H
#define INC_408DEBUGGER_FUNC_H

#include <string_view>
#include <unordered_map>

typedef struct F {
    int nCalls;
    std::string_view name;
    std::unordered_map<std::string_view, int> pairs;
}func;

func * newFunc(std::string_view);
int addPair(func *, std::string_view);
bool find(func *, std::string_view);

#endif
