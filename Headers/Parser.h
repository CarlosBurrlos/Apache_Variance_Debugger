#ifndef INC_408DEBUGGER_PARSER_H
#define INC_408DEBUGGER_PARSER_H

class Parser {

public:

    Parser(){}
    ~Parser(){}

    bool checkAndConsume();  //bool checkAndConsume(std::list<int>); Implement later
    bool parseWord();        bool check(int);
    bool parsePreProc();     bool parseArgs(Func *);
    bool parseProto();       bool parseScope();
    bool parseFuncBody();    bool parseFuncCall();

    void parse();
    void consume();          void consumeLine();

private:

    void Parser::enterScope(Scope * s) {
        scope = s;
    }

    void Parser::exitScope() {

        if (scope) {
            std::pair<std::string_view, Scope *> pair(scope->getScope(), scope);
            allScopes.insert(pair);
            this->scope = nullptr;
        }
    }

    Scope * scope;              Scanner * scanner;
};

#endif //INC_408DEBUGGER_PARSER_H
