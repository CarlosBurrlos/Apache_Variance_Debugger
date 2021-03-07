#include "Header.h"

using namespace Dbugr;

void Parser::parse() {
    if (this->scanner->getCurrType() == 1) //entrScp
        parseScope(this->scanner->getCurrStr());
    else if (this->scanner->getCurrType() == 2) //extScp
        exitScope();
    else if (this->scanner->getCurrType() == 3) //funcCall
        parseFunc(this->scanner->getCurrStr());
    else if (this->scanner->getCurrType() == 4) //return
        ; //TODO::Handle? Yes? No?
    else if (this->scanner->getCurrType() == 6) //params
        ; //TODO::Handle? Yes? No?
}

//Gets a the new func string and creates func itm and stores it
void Parser::parseFunc(std::string s) {
    Func * func = new Func(s);
    std::pair <std::string, Func *> p(func->getFunc(), func);
    this->scp->addFunc(p);
}

//Gets a the new scope string and creates scope itm and stores it
void Parser::parseScope(std::string s) {
    //When we are going to create a new scope all we want to do
    //is enter a new scope and swap out the old
    if (!this->scp) {
        //If we haven't processed a scope yet, we will handle this
        this->scp = enterNScope(this->scanner->getCurrStr());
    }
    else {
        //Add the current scope to the Scopes table
        Scopes.push_back(this->scp);
        this->scp = enterNScope(this->scanner->getCurrStr());
    }
}

void Parser::done() {
    exitScope();
}

Scope * Parser::enterNScope(std::string name) {

    Scope * s = new Scope(name);
    this->scp = s;

    return s;
}

void Parser::exitScope() {
    
}

void addNScope() {

}

void Parser::addNFun() {

}

void checkIfParsed() {

}
