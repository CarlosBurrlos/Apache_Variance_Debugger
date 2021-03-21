#include "../Headers/Scope.h"

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

void Scope::addFunc(std::pair <std::string_view , Func*> p) {
    funcs.insert(p);
}

void Scope::setArgs(char * args, int len) {
    scopeArgs = args;
    argsSize = len;
}

bool Scope::contains(std::string_view s) {
    auto i = funcs.find(s);
    if (i == funcs.end())
        return 0;
    nOccurs++;
    return 1;
}
bool Scope::hasFunc(std::string_view func) {
    return (funcs.find(func) == funcs.end());
}

