#include "../include/Invar.h"
#include "../include/Globals.h"

#include <iostream>


void compute_support(scp * scope) {
    auto funcs = scope->Funcs;
    std::unordered_map<std::string_view, func *>::iterator i;
    std::unordered_map<std::string_view, func *>::iterator j;

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
    scp * currScope;
    func * currFunc;
    for (auto const & [ key, value ] : Scopes) {
        currScope = value;
        for (auto const & [ key, value ] : currScope->Funcs) {
            currFunc = value;
            for ( auto const & [ key, value ] : currFunc->pairs) {
                std::string_view pair = key;
                //bug: (...) in scopeN pair: ((...),(...)), support: N, confidence: 00.00%
                if (!find(currScope, pair)) {
                    std::cout << "bug: " << currFunc->name << " in " << currScope->name << ',';
                    std::cout << " pair: " << '(' << currFunc->name << ',' << pair << "),";
                    std::cout << " support: " << value << ',';
                    std::cout << " confidence: " << (100 * ((double)value/ currFunc->nCalls)) << '%' << '\n';
                }
            }
        }
    }
}




