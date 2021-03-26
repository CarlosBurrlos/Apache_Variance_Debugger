#ifndef INC_408DEBUGGER_PARSER_H
#define INC_408DEBUGGER_PARSER_H
#include "Scope.h"
class Parser {

public:

    Parser(Scanner * s){ scanner = s;}
    ~Parser(){}

    bool checkAndConsume(int);  //bool checkAndConsume(std::list<int>); Implement later
    bool parseWord();        bool check(int);
    bool parsePreProc();     bool parseArgs(Func *);
    bool parseProto();       bool parseScope();
    bool parseFuncBody();    bool parseFuncCall();

    bool parse();
    void consume();          void consumeLine();

private:

    void enterScope(Scope * s) {
        scope = s;
    }

    void exitScope() {

        if (scope) {
            std::pair<std::string_view, Scope *> pair(scope->getScope(), scope);
            allScopes.insert(pair);
            this->scope = nullptr;
        }
    }

    Scope * scope;              Scanner * scanner;
};

#endif //INC_408DEBUGGER_PARSER_H
