//
// Created by Carlos on 3/17/21.
//

#ifndef INC_408DEBUGGER_TOKENS_H
#define INC_408DEBUGGER_TOKENS_H

#include <regex>

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
const char * PREPROC         = "#(include|define)";

std::regex WORD("\\w+");
std::regex RET("int | void");
std::regex PPROC(PREPROC);

#endif //INC_408DEBUGGER_TOKENS_H
