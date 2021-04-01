#include "../Headers/All.h"

void scan() {

}

void output() {

}

//NOTE:: What we could do is only use the strings for the funcs + therfore concat
//How will we keep track of the pairs that we have already seen?

//We could possibly compute and store the hashes at the beginning?
    // > We could then store both hashes and therefore, wouldn't have to recompute

    //TODO:: We want to parse the parse dynamically while we are parsing the scopes
    // >> If we don't, we will end up with an n^2 solution

double compute_support() {
    for (const auto & [ key, value ] : allScopes) {
        if (key == "main(") continue;
        auto funcs = value->getFuncs();
        size_t n_hash;

        int i = 0;
        int j;
        while (i < funcs.size() - 1) {
            for (int x = i, j = funcs.size() - 1; i <= j; x++, j--) {
                n_hash = funcs[i].first ^ funcs[j].first;
                if (Invars.find(n_hash) == Invars.end()) {
                    //We have a new pair that we can add
                    auto * invar = new Invar;
                    invar->support++;
                    Invars.insert( {n_hash, invar} );
                }
                else {
                    Invars.find(n_hash)->second->support++;
                }
            }
        }
    }
    return 0.0;
}



