#ifndef INC_408DEBUGGER_FUNC_H
#define INC_408DEBUGGER_FUNC_H

#include <string_view>
#include <unordered_map>

class Func {
public:
    Func(std::string_view);
    ~Func();

    int getNCalls();
    void setNCalls();               void setArgs(char *, int);
    std::string_view getName();     std::string_view getArgs();
    Scope * convertToScope();
    std::unordered_map<std::string_view, int> pairs;
private:
    int nOccurs;            int argsSize;
    char * funcArgs;
    std::string_view funcName;
};

#endif
