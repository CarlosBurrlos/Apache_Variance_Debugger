#ifndef INC_408DEBUGGER_DEBUGGER_H
#define INC_408DEBUGGER_DEBUGGER_H

#include    <unordered_map>
#include    <unordered_set>
#include    <string_view>

class Parser;
class Scanner;
class Scope;
class Func;

class Errors{
        //TODO:: construct an error class that will allow us to throw -> STDERR
        //Question to consider, do we want to output to a file or just to STDOUT
};

#endif