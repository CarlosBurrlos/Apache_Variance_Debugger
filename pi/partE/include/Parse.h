#ifndef INC_408DEBUGGER_PARSE_H
#define INC_408DEBUGGER_PARSE_H

#include "Scanner.h"
#include "Scope.h"
#include <list>

class Parse {
public:
    Parse(Scanner *);          ~Parse();

    bool parse();
    bool parseNullFunc();      bool parseFuncNode();
    bool parseScopeNode();     bool parseFunc();
    bool parseFuncCall();      bool parseNodes();

    int consume();

    bool check(int);           bool checkAndConsume(int);
    bool check(std::list<int>);

private:
    func * scope;               Scanner * scanner;
};


#endif //INC_408DEBUGGER_PARSE_H
