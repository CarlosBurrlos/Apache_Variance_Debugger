#ifndef INC_408DEBUGGER_NFAS_H
#define INC_408DEBUGGER_NFAS_H

#define SCOPE       1
#define SCOPENODE   2
#define NULLFUNC    3
#define FUNCNODE    4
#define FUNC        5
#define PRINTF      6
#define MAIN        7
#define FUNCADDR    8
#define USES        9
#define BAD         0


class NFAs {
public:

    NFAs(): wordStart(0), wordEnd(0), temp(0){}
    ~NFAs() {wordStart = wordEnd = temp = 0;}

    int compute();
    int getScope();     int getScopeNode();
    int getFuncNode();  int getNullFunc();

    int getPrintf();    int getFuncName();
    int getMain();      int getUses();
    int getFuncAddr();

    void setWordStart(char * front, char * end) {wordStart = front; wordEnd = end;}

private:
    char * wordStart;   char * wordEnd;
    char * temp;
};

#endif
