//
#include "../Headers/All.h"

func * newFunc(std::string_view fName) {
    const auto f = new func;
    f->name = fName;
    f->nCalls = 0;
    return f;
}

int addPair(func * fnc, std::string_view fName) {
    fnc->pairs.insert( {fName, 0} );
    return fnc->pairs.size();
}

bool find(func * fnc, std::string_view func) {
    return (fnc->pairs.find(func) == fnc->pairs.end());
}
