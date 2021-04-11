#include "../include/Parse.h"
#include "../include/Globals.h"
#include "../include/Invar.h"

#include <algorithm>
#include <cassert>
#include <iostream>

//======= Helpers =======
bool Parse::check(int token) {
	return (token == Token);
}

bool Parse::checkAndConsume(int token) {
	if (check(token)) {
		consume();
		return true;
	}
	return false;
}

bool Parse::check(std::list<int> tokens) {for (auto const& t : tokens){if (t == Token)return true;} return false;}
int Parse::consume() {
	return scanner->readWord();
}
//======= Helpers =======

Parse::Parse(Scanner * s)
: scope(0), scanner(s) {}

Parse::~Parse() {
    scope = 0;
}

bool Parse::parse() {
    if(parseNullFunc()) {
        
	 while (1) {
	    bool retVal = parseNodes();
            if(retVal == false) {
		    break;
	    }
	}
        if (scanner->atEnd) {
		//======= DB
		 /*for (auto const & [ key, value ] : Functions) {
			std::cout << "FUNC Name:: " << key << '\n';
			for (auto const & [ key, value ] : value->pairs) {
				std::cout << "PAIR:: " << key << "  SUPP:: " << value << '\n';
			}
		}
		*/
		//======= DB
            	scan_for_bugs();
            return true;
        }
        return false;
    }
    return false;
}

bool Parse::parseNodes() {
    if (scanner->atEnd) return false;
    if (check(FUNCNODE)) {
        if (parseFuncNode()) {
            compute_support(scope);
            return true;
        }
    }
    else if (check({PRINTF, MAIN})) {
        if (check(MAIN)) {
            consume();
            while (!check({FUNCNODE, PRINTF}))
                consume();
        }
        else if (check(PRINTF)) {
            consume();
            while (!check(FUNCNODE))
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
	std::cout << "NAME:: " << fName <<'\n';
        f->name = fName;
        Functions.insert(std::make_pair(fName, f));
        consume();
        return true;
    }
    else if (check(MAIN)) {
        goto function;
    }
    else if (check(PRINTF)) {
        goto function;
    }
    return false;
}

bool Parse::parseFuncNode() {
    if (check(FUNCNODE)) {
        std::string_view fName = scanner->getCurrStr();
	std::cout << "FNAME:: " << fName << '\n';
	func * f;
	if (Functions.find(fName) == Functions.end()) {
		std::cout << "Couldnt find function" << '\n';
		std::cout << fName << '\n';
		f = new func();
		Functions.insert({fName, f});
	}
	else {
		f = Functions.at(fName);
        	scope = f;
	}
	consume();
        if (checkAndConsume(FUNCADDR)) {
            char * tmp = 0;
            long uses;
            uses = strtol(scanner->getCurrWrdPtr(), &tmp, 10) - 1;
	    f->nCalls = uses;
	    consume();
            while (check(FUNC)) {
                    parseFunc();
            }
            return true;
        }
    }
    return false;
}

bool Parse::parseFunc() {
    std::string_view fName = scanner->getCurrStr();
    func * f;
    if (Functions.find(fName) == Functions.end()) {
    	f = new func();
	f->name = fName;
	Functions.insert({fName, f});
    }
    else {
    	func * f = Functions.at(fName);
    }
    scope->funcs.insert({fName, f});
    consume();
    return true;
}
