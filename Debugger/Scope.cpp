#include "../Headers/All.h"

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

void Scope::addFunc(size_t hash, Func * func) {
    int idx = funcs.size();
    funcs.insert({idx, {hash, func}});
}

void Scope::setArgs(char * args, int len) {
    scopeArgs = args;
    argsSize = len;
}