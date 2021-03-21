#ifndef INC_408DEBUGGER_FUNC_H
#define INC_408DEBUGGER_FUNC_H

class Func {
public:
    Func(std::string_view name)
            :nOccurs(0), funcArgs(nullptr),
             funcName(name)
    {}

    ~Func()
    {
        nOccurs = 0;
        funcArgs = nullptr;     funcName = nullptr;
    }

    int getNCalls()               {return this->nOccurs;}
    void setNCalls()              {this->nOccurs++;}
    void setArgs(char * c, int n) {this->funcArgs = c, this->argsSize = n;}

    std::string_view getName()    {return funcName;}
    std::string_view getArgs()
    {return std::string_view(funcArgs, argsSize);}

private:

    int nOccurs;            int argsSize;
    char * funcArgs;
    std::string_view funcName;
};

#endif //INC_408DEBUGGER_FUNC_H
