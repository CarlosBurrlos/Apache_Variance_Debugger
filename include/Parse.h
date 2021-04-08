//
// Created by Carlos Burroughs on 4/8/21.
//

#ifndef INC_408DEBUGGER_PARSE_H
#define INC_408DEBUGGER_PARSE_H

#include "Scanner.h"
#include "Scope.h"
#include <list>

class Parse {
public:
    //Constructor & Destructor
    Parse(Scanner *);
    ~Parse();
    //Driver code
    bool parse();
    bool parseNullFunc();
    //Consume
    int consume();             int consumeLine();
    //Checks
    bool check(int);           bool checkAndConsume(int);
    bool check(std::list<int>);
private:
    scp * scope;               Scanner * scanner;
};


#endif //INC_408DEBUGGER_PARSE_H
