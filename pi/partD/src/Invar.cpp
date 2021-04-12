#include "../include/Invar.h"
#include "../include/Globals.h"

#include <iostream>


void compute_support(scp * scope) {
    auto funcs = scope->Funcs;
    std::unordered_map<std::string_view, func *>::iterator i;
    std::unordered_map<std::string_view, func *>::iterator j;
    for (i = funcs.begin(); i != funcs.end(); i++) {
        for (j = i, j++; j != funcs.end(); j++) {
		//Here is where we are setting the normal order. When we recognize a pair for the first
		//time, we will then store the pair of ints (one for regular support, one for the 
		//flipped pair support) and then the first item in the pair as a string_view.
            if (i->second->pairs.find(j->first) == i->second->pairs.end()) {
                i->second->pairs.insert( std::make_pair( j->first, std::make_pair( std::make_pair(1, 0), i->first ) ) );
                j->second->pairs.insert( std::make_pair( i->first, std::make_pair( std::make_pair(1, 0), i->first ) ) );
            }
            else {
		//Here we will be incrementing the integer values accordingly. If it is order 1
		//increment the first int.
		//Otherwise increment the second int
                i->second->pairs.at(j->first).first.first++;
                j->second->pairs.at(i->first).first.first++;
            }
        }
    }
}

void scan_for_bugs() {
    scp * currScope;
    func * currFunc;
    /*For all scopes*/for (auto const & [ key, value ] : Scopes) {
        currScope = value;
        /*For all funcs in scope S*/for (auto const & [ key, value ] : currScope->Funcs) {
            currFunc = value;
            /*For all pairs in func F*/for ( auto const & [ key, value ] : currFunc->pairs) {
                std::string_view pair = key;
                if (!find(currScope, pair)) {
                    double invarCompute = (100 * ((double) value.first.first / currFunc->nCalls));
                    if (invarCompute >= T_CONFIDENCE && value.first.first >= T_SUPPORT) {
			//This is where we compute the second invariance
			//This value is computed with the second int inside the <int, int> pair
			//and will be compared against the first invariance.
			//If it is greater, this is the bug we print
			double secondInvarCompute = (100 * ((double) value.first.second / currFunc->nCalls)); 
                        std::cout << "bug: " << currFunc->name << " in " << currScope->name << ',';
			if (secondInvarCompute > invarCompute) {
			    if (currFunc->name < pair)
                                std::cout << " pair: " << '(' << currFunc->name << ',' << pair << "),";
                            else 
                                std::cout << " pair: " << '(' << pair << ',' << currFunc->name << "),";
                            std::cout << " support: " << value.second << ',';
                            std::cout.precision(2);
                            std::cout << " confidence: " << std::fixed << secondInvarCompute << '%' << '\n';

			}
			else {
			    if (currFunc->name < pair)
                                std::cout << " pair: " << '(' << currFunc->name << ',' << pair << "),";
                            else 
                                std::cout << " pair: " << '(' << pair << ',' << currFunc->name << "),";
                            std::cout << " support: " << value.second << ',';
                            std::cout.precision(2);
                            std::cout << " confidence: " << invarCompute << '%' << '\n';

			}
                    }
                }
            }
        }
    }
}




