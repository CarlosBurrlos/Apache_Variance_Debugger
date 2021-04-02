#include "../Headers/All.h"

struct S {
    std::string_view name;
    std::map <std::string_view, Func *> Funcs;
};

scope * newScope() {
    const auto s = new scope;
    s->name = nullptr;
    return s;
}


//===== So we don't have too much overhead

std::string_view getScopeName() {

}

std::map <std::string_view, Func *> getFuncs() {

}


Scope::Scope(std::string_view name)
        :nOccurs(0),   scopeArgs(nullptr),
         scopeName(name)
{}

Scope::~Scope() {
    this->nOccurs = 0;
    scopeArgs = nullptr;
    scopeName = nullptr;
}

std::string_view Scope::getScope() {
    return scopeName;
}
char * Scope::getRetType() {
    return retType;
}

void Scope::addFunc(std::string_view string, Func * func) {
    funcs.insert( {string, func} );
}

void Scope::setArgs(char * args, int len) {
    scopeArgs = args;
    argsSize = len;
}