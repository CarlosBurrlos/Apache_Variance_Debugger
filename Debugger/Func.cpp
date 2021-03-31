//
// Created by Carlos on 3/27/21.
//
#include "../Headers/All.h"


Func::Func(std::string_view name)
:nOccurs(0), funcArgs(nullptr),
funcName(name) {}

Func::~Func()
{
    nOccurs = 0;
    funcArgs = nullptr;
    funcName = nullptr;
}

int  Func::getNCalls()              {return this->nOccurs;}
void Func::setNCalls()              {this->nOccurs++;}
void Func::setArgs(char * c, int n) {this->funcArgs = c, this->argsSize = n;}

std::string_view Func::getName()    {return funcName;}
std::string_view Func::getArgs()    {return std::string_view(funcArgs, argsSize);}

Scope * Func::convertToScope() {
    Scope * s = nullptr;
    std::string_view name = funcName;
    if (allFuncs.find(name) == allFuncs.end()) {
        return s;
    }
    s = new Scope(name);
    assert(s);
    s->setArgs(funcArgs, argsSize);
    allScopes.insert( {name, s} );
    return s;
}