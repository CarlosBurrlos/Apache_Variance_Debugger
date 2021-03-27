#ifndef INC_408DEBUGGER_PARSER_H
#define INC_408DEBUGGER_PARSER_H
#include "Scope.h"
class Parser {

public:

    Parser(Scanner * s){ scanner = s;}
    ~Parser(){}

    bool checkAndConsume(int);  bool check(int);
    bool parseArgs(Func *);     bool parseFuncBody();
    bool parseFuncCall();       bool parseFunc();
    bool parse();               bool  atEnd();
    bool parsePreProc();

    void consume();             void consumeLine();

private:
    Scope * scope;              Scanner * scanner;
};

#endif //INC_408DEBUGGER_PARSER_H
