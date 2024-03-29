#include "../include/Invar.h"
#include "../include/Globals.h"

#include <iostream>


void compute_support(func * scope) {
    auto funcs = scope->funcs;

    std::unordered_map<std::string_view, func *>::iterator i;
    std::unordered_map<std::string_view, func *>::iterator j;

    for (i = funcs.begin(); i != funcs.end(); i++) {
        for (j = i, j++; j != funcs.end(); j++) {
            if (i->second->pairs.find(j->first) == i->second->pairs.end()) {
                i->second->pairs.insert( std::make_pair(j->first, 1) );
                j->second->pairs.insert( std::make_pair(i->first, 1) );
            }
            else {
                i->second->pairs.at(j->first)++;
                j->second->pairs.at(i->first)++;
            }
        }
    }
}

void scan_for_bugs() {
    func * currScope;
    func * currFunc;
    for (auto const & [ key, value ] : Functions) {
        currScope = value;
		for ( auto const & [ key, value ] : currScope->funcs) {
		    currFunc = value;
		    for ( auto const & [ key, value ] : currFunc->pairs) {
		        std::string_view pair = key;
		        if (currScope->funcs.find(pair) == currScope->funcs.end()) {
		            double invarCompute = (100.00 * (((double) value) / ((double)currFunc->nCalls)));
		            bool check = (invarCompute >= T_CONFIDENCE);
		            if (invarCompute >= T_CONFIDENCE) {
                        	if ((value >= T_SUPPORT)) {
                            		std::cout << "bug: " << currFunc->name << " in " << currScope->name << ',';
                            		if (currFunc->name < pair) {
                                		std::cout << " pair: " << '(' << currFunc->name << ", " << pair << "),";
                            		}
                            		else {
                                		std::cout << " pair: " << '(' << pair << ", " << currFunc->name << "),";
                            		}
                            		std::cout << " support: " << value << ',';
					printf(" confidence: %.2f%%\n", invarCompute);
                            		//std::cout << " confidence: " << std::fixed << (100 * ((double) value / currFunc->nCalls))
                                      		//<< '%' << '\n';
                        	}
		            }
		        }
		    }
		}
	}
}




