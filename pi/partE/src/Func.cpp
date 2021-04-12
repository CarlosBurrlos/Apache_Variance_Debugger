#include "../include/Func.h"

func * newFunc(std::string_view fName) {
    const auto f = new func;
    f->name = fName;
    f->nCalls = 0;
    f->pairs.clear();
    return f;
}

int addPair(func * fnc, std::string_view fName) {
    auto nFunc = std::make_pair(fName, 0);
    fnc->pairs.insert(nFunc);
    return fnc->pairs.size();
}

bool find(func * fnc, std::string_view func) {
    bool val = (fnc->pairs.find(func) == fnc->pairs.end());
    return val;
}
