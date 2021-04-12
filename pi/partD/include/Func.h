#ifndef INC_408DEBUGGER_FUNC_H
#define INC_408DEBUGGER_FUNC_H

#include <string_view>
#include <unordered_map>

typedef struct F {
    int nCalls;
    //A counter to keep track of the flipped order pair (i.e. BA)
    int flip;
    std::string_view name;
    //unordered_map storing as value a pair of two ints (pair) and the string view
    //This new string_view holds the initial order for the pair
    //(e.g. If the pair is observed as AB, this value will be A for both pairs)
    std::unordered_map<std::string_view, std::pair<std::pair<int, int>, std::string_view>> pairs;
}func;

func * newFunc(std::string_view);
int addPair(func *, std::string_view);
bool find(func *, std::string_view);

#endif
