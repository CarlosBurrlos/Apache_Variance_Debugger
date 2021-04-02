#include "../Headers/All.h"
#include <iostream>


void compute_support(Scope * scope) {
    auto funcs = scope->getFuncs();
    std::unordered_map<std::string_view, Func*>::iterator i;
    std::unordered_map<std::string_view, Func*>::iterator j;

    for (i = funcs.begin(); i != funcs.end(); i++) {
        for (j = i, j++; j != funcs.end(); j++) {
            if (i->second->pairs.find(j->first) == i->second->pairs.end()) {
                i->second->pairs.insert( {j->first, 1} );
                j->second->pairs.insert( {i->first, 1} );
            }
            else {
                i->second->pairs.at(j->first)++;
                j->second->pairs.at(i->first)++;
            }
        }
    }
}

void scan_for_bugs() {
    //Go through the global scopes and check each function within the scope and compute the values
    Scope * currScope;
    Func * currFunc;
    for (auto const & [ key, value ] : allScopes) {
        currScope = value;
        for (auto const & [ key, value ] : value->getFuncs()) {
            currFunc = value;
            for ( auto const & [ key, value ] : currFunc->pairs) {
                if (!currScope->find(key)) {
                    std::cout << "Bug in" << currScope->getScope() << '\n';
                }
            }
        }
    }
}




