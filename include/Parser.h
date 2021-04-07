#ifndef INC_408DEBUGGER_PARSER_H
#define INC_408DEBUGGER_PARSER_H

#include    "../include/Scanner.h"

class Parser {

public:

    Parser(Scanner * s):scope(0){ scanner = s;}
    ~Parser(){scope = 0;}

    bool checkAndConsume(int);  bool check(int);
    bool parseFuncBody();       bool parseFuncCall();
    bool parseFunc();           bool parse();
    bool  atEnd();              bool parsePreProc();
    bool parseScope();

    void consume();

private:
    //TODO::Initialize scope
    scp * scope;              Scanner * scanner;
};

#endif //INC_408DEBUGGER_PARSER_H
