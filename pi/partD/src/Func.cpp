#include "../include/Func.h"

func * newFunc(std::string_view fName) {
    const auto f = new func;
    f->name = fName;
    f->nCalls = 0;
    f->pairs.clear();
    return f;
}

