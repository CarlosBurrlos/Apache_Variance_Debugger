#include "../include/Scope.h"

scp * newScope(std::string_view sName) {
    const auto s = new scp;
    s->name = sName;
    return s;
}

int addFunc(scp * scp,  func * f) {
    scp->Funcs.insert( {f->name, f} );
    return scp->Funcs.size();
}

bool find(scp * scp, std::string_view func) {
    return (scp->Funcs.find(func) != scp->Funcs.end());
}