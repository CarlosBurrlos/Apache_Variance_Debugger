#ifndef INC_408DEBUGGER_FUNC_H
#define INC_408DEBUGGER_FUNC_H

#include <string_view>

class Func {
public:
    Func(std::string_view);
    ~Func();

    int getNCalls();
    void setNCalls();               void setArgs(char *, int);
    std::string_view getName();     std::string_view getArgs();
    Scope * convertToScope();

private:
    int nOccurs;            int argsSize;
    char * funcArgs;
    std::string_view funcName;
};

#endif
