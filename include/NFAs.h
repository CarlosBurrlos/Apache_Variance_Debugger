#ifndef INC_408DEBUGGER_NFAS_H
#define INC_408DEBUGGER_NFAS_H
/*
#define BAD         0
#define PREPROC     1
#define FUNC        2
#define SCOPE       3
#define RETVOID     4
#define RETINT      5
#define RETRN       6
#define ARGS        7
#define EXT_SCOPE   8
#define ENTR_SCOPE  9
#define FUNCADDR    10
#define USES        11
#define NULLFUNC    12
*/
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
