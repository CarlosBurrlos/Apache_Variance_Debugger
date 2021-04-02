#ifndef INC_408DEBUGGER_SCOPE_H
#define INC_408DEBUGGER_SCOPE_H

#include <string_view>
#include <unordered_map>
#include <vector>
#include <map>

class Scope {

public:

    explicit Scope(std::string_view);
    ~Scope();

    int   getNCalls() {return nOccurs;}

    std::string_view getScope();

    char * getRetType();

    void addFunc(std::string_view, Func*);
    void setArgs(char *, int);              void setNFuncs(int n) {nFuncs = n;}
    bool find(std::string_view s) {return (funcs.find(s) == funcs.end());}
    std::unordered_map<std::string_view, Func*> getFuncs() {return funcs;}

    std::string_view getArgs()              {return std::string_view(scopeArgs, argsSize);}
private:

    int     nOccurs;            int argsSize;
    int     nFuncs;

    char * scopeArgs;           std::string_view scopeName;
    char * retType;
    std::unordered_map<std::string_view , Func *> funcs;
};

#endif //INC_408DEBUGGER_SCOPE_H
