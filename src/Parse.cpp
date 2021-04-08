//
// Created by Carlos Burroughs on 4/8/21.
//

#include "../include/Parse.h"
#include "../include/Globals.h"

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
    parseNullFunc();
    return 0;
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

