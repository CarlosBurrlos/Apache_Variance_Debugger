#ifndef INC_408DEBUGGER_FUNC_H
#define INC_408DEBUGGER_FUNC_H
#include "Globals.h"

#include <string_view>
#include <unordered_map>

func * newFunc(std::string_view);
int addPair(func *, std::string_view);
bool find(func *, std::string_view);

#endif
