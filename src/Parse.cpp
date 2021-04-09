//
// Created by Carlos Burroughs on 4/8/21.
//

#include "../include/Parse.h"
#include "../include/Globals.h"
#include "../include/Func.h"
#include "../include/Scope.h"
#include "../include/Invar.h"

#include <algorithm>
#include <execution>

bool Parse::check(int token) {return (token == Token);}
bool Parse::checkAndConsume(int token) {if (check(token)) {consume();return true;} return false;}
bool Parse::check(std::list<int> tokens) {for (auto const& t : tokens){if (t == Token)return true;} return false;}
int Parse::consume() {return scanner->readWord();}
int Parse::consumeLine() {return scanner->readLine();}

Parse::Parse(Scanner * s)
: scanner(s)
{
    //Read all of the characters before '<'
    scanner->readTill('<');
};

Parse::~Parse() {

}

bool Parse::parse() {
    //Maybe we could do somethingn within the parse constructor that would
    //allow us to consume all of the characters before the '<'
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
           return true;
        }
    }
    else if (check(FUNCNODE)) {
        if (parseFuncNode()) {
            return true;
        }
    }
    return false;
}

bool Parse::parseNullFunc() {
    consume();
    if (check(NULLFUNC)) {
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
        func * f = (func *) malloc(sizeof(func));
        assert(f);
        std::string_view fName = scanner->getCurrStr();
        Functions.insert(std::make_pair(fName, f));
        consume();
        return true;
    }
    else if (check(SCOPE)) {
        scope:
        scp * s = (scp *) malloc(sizeof(scp));
        assert(s);
        std::string_view sName = scanner->getCurrStr();
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
    if (checkAndConsume(FUNCNODE)) {
        if (check(USES)){
            //use atoi() to get the value;
            consume();
            while (!check({SCOPENODE, FUNCNODE}))
                consume();
            return true;
        }
    }
    return false;
}

bool Parse::parseFunc() {
    std::string_view fName = scanner->getCurrStr();
    if (Functions.find(fName) == Functions.end()) {
        //This shouldn't happen
        return false;
    }
    func * f = Functions.at(fName);
    scope->Funcs.insert(std::make_pair(fName, f));
    consume();
    return true;
}

bool Parse::parseScopeNode() {
    if (checkAndConsume(SCOPENODE)) {
        std::string_view sName = scanner->getCurrStr();
        if (Scopes.find(sName) == Scopes.end()) {
            //This would throw error
            return false;
        }
        scp * s = Scopes.at(sName);
        scope = s;
        consume(); consume();
        while (check({SCOPE, FUNC})) {
            if (check(SCOPE)) {
                parseScope();
            }
            else {
                parseFunc();
            }
        }
    }
    return false;
}

bool Parse::parseScope() {
    consume();
    return true;
}



