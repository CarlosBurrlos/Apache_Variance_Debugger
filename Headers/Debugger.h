#ifndef INC_408DEBUGGER_DEBUGGER_H
#define INC_408DEBUGGER_DEBUGGER_H

#include    <unordered_map>
#include    <unordered_set>
#include    <string_view>

const char * SEMICOL         = ";";
const char * LPAREN          = "(";
const char * RPAREN          = ")";
const char * POUND           = "#";
const char * COM             = ",";
const char * NLINE           = "\n";
const char * TAB             = "\\t";
const char * SPACE           = " ";
const char * MAIN            = "main";
const char * LBRACKET        = "{";
const char * RBRACKET        = "}";
const char * INCLUDE         = "include";
const char * DEFINE          = "define";
const char * PROC            = "#(include|define)";


class Parser;
class Scanner;
class Scope;
class Func;

std::unordered_map<std::string_view/*scpName*/, Scope *> allScopes;
std::unordered_map<std::string_view/*Name*/,Func *> allFuncs;

extern int Token;

class Errors{
        //TODO:: construct an error class that will allow us to throw -> STDERR
        //Question to consider, do we want to output to a file or just to STDOUT
};

#endif