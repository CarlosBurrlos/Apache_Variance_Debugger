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
        while (parseFunc())
            ;
        scan_for_bugs();
        return true;
    }
    return false;
}
//We want to consume until we either reach \' or \<<
bool Parse::parseNullFunc() {
    consume();
    if (check(0)) { //0 = NULLFUNC
        consumeLine();
        if (check(1)) { //1 = CS
            scanner->readTill('\'');
            consume();
            if (check({2, 3}))  //2 = func 3 = Scope
            {
                switch (Token) {
                    case 2:
                        //Add to funcs
                        ;
                    case 3:
                        //Add to Scopes
                        ;
                    default:
                        //Do nothing
                        ;
                }
            }
        }
        return true;
    }
    return false;
}

bool Parse::parseFunc() {
    scanner->readTill('\'');
    consume();
    if (check({2, 3})) {
        if (check(3)) {
            return parseScope();
        }
        func * f = Functions.at(scanner->getCurrStr());
        scanner->readTill('#');
        if (check(4)) {   //4 = USES

            //Will have to think of some way to check if this is an int
        }
        //Parse the func accordingly
        //We don't need to expand it so just read rest of the line
    }

    return false;
}

bool Parse::parseScope() {
    consumeLine();
    scanner->readTill('\'');
    consume();
    if (check(2)) { //We have grabbed a function

    }
    return false;
}

bool Parse::parseFuncCall() {
    return 1;
}

