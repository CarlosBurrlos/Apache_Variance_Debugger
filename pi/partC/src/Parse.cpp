#include "../include/Parse.h"
#include "../include/Globals.h"
#include "../include/Invar.h"

#include <algorithm>
#include <cassert>
#include <iostream>

//======= Helpers =======
bool Parse::check(int token) {return (token == Token);}
bool Parse::checkAndConsume(int token) {if (check(token)) {consume();return true;} return false;}
bool Parse::check(std::list<int> tokens) {for (auto const& t : tokens){if (t == Token)return true;} return false;}
int Parse::consume() {return scanner->readWord();}
//======= Helpers =======

Parse::Parse(Scanner * s)
: scope(0), scanner(s) {}

Parse::~Parse() {
    scope = 0;
}

bool Parse::parse() {
    if(parseNullFunc()) {
        while (parseNodes())
            ;
        if (scanner->atEnd) {
            scan_for_bugs();
            return true;
        }
        return false;
    }
    return false;
}

bool Parse::parseNodes() {
    if (scanner->atEnd) return false;
    if (check(SCOPENODE)) {
        if (parseScopeNode()) {
            compute_support(scope);
            return true;
        }
    }
    else if (check(FUNCNODE)) {
        if (parseFuncNode()) {
            return true;
        }
    }
    else if (check({PRINTF, MAIN})) {
        if (check(MAIN)) {
            consume();
            while (!check(PRINTF))
                consume();
        }
        else if (check(PRINTF)) {
            consume();
            while (!check({FUNCNODE, SCOPENODE}))
                consume();
        }
        return true;
    }
    return false;
}

bool Parse::parseNullFunc() {
    consume();
    if (checkAndConsume(NULLFUNC)) {
        if (checkAndConsume(FUNCADDR)) {
            consume();  //uses - not needed for nullfunc
            while (parseFuncCall()) //Will parse our funcs and allocate structs
                ;
            return true;
        }
        return false;
    }
    return false;
}

bool Parse::parseFuncCall() {
    if (check(FUNC)) {
        function:
        func * f = new func();
	assert(f);
        std::string_view fName = scanner->getCurrStr();
        f->name = fName;
        Functions.insert(std::make_pair(fName, f));
        consume();
        return true;
    }
    else if (check(SCOPE)) {
        scope:
        scp * s = new scp();
        assert(s);
        std::string_view sName = scanner->getCurrStr();
        s->name = sName;
        Scopes.insert(std::make_pair(sName, s));
        consume();
        return true;
    }
    else if (check(MAIN)) {
        goto scope;
    }
    else if (check(PRINTF)) {
        goto function;
    }
    return false;
}

bool Parse::parseFuncNode() {
    if (check(FUNCNODE)) {
        std::string_view fName = scanner->getCurrStr();
        consume();
        if (checkAndConsume(FUNCADDR)) {
            char * tmp = 0;
            long uses;
            uses = strtol(scanner->getCurrWrdPtr(), &tmp, 10) - 1;
            func * f = Functions.at(fName);
            f->nCalls = (int)uses;
            consume();
            while (!check({SCOPENODE, FUNCNODE, MAIN}) && !scanner->atEnd)
                consume();
            return true;
        }
    }
    return false;
}

bool Parse::parseScopeNode() {
    if (check(SCOPENODE)) {
        std::string_view sName = scanner->getCurrStr();
        scp *s = Scopes.at(sName);
        scope = s;
        consume();
        if (checkAndConsume(FUNCADDR)) {
            consume();
            while (check({SCOPE, FUNC, PRINTF, MAIN}) && !scanner->atEnd) {
                if (checkAndConsume(SCOPE)) {
                    continue;
                }
                else if(check(FUNC)) {
                    parseFunc();
                }
                else if (checkAndConsume(PRINTF)) {
                    continue;
                }
                else if (checkAndConsume(MAIN)) {
                    continue;
                }
            }
            return true;
        }
    }
    return false;
}

bool Parse::parseFunc() {
    std::string_view fName = scanner->getCurrStr();
    func * f = Functions.at(fName);
    scope->Funcs.insert({fName, f});
    consume();
    return true;
}
