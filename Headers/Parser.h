#ifndef INC_408DEBUGGER_PARSER_H
#define INC_408DEBUGGER_PARSER_H

class Parser {

public:

    Parser(){}
    ~Parser(){}

    void parse();            bool parseWord();
    bool parsePreProc();     bool parseArgs(Func *);
    bool parseProto();       bool parseScope();
    bool parseFuncBody();    bool parseFuncCall();

    void consume();          void consumeLine();

private:

    void enterScope(Scope *);   void exitScope();

    Scope * scope;              Scanner * scanner;
};

#endif //INC_408DEBUGGER_PARSER_H
