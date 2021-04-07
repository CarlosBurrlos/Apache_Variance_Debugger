#ifndef INC_408DEBUGGER_PARSER_H
#define INC_408DEBUGGER_PARSER_H

class Parser {

public:

    Parser(Scanner * s){ scanner = s;}
    ~Parser(){}

    bool checkAndConsume(int);  bool check(int);
    bool parseFuncBody();       bool parseFuncCall();
    bool parseFunc();           bool parse();
    bool  atEnd();              bool parsePreProc();
    bool parseScope();

    void consume();

private:
    scp * scope;              Scanner * scanner;
};

#endif //INC_408DEBUGGER_PARSER_H
