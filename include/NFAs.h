#ifndef INC_408DEBUGGER_NFAS_H
#define INC_408DEBUGGER_NFAS_H

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

class NFAs {
public:

    //TODO::Initialize wordEnd to zero/null and Initialize temp to null

    NFAs(): wordStart(0), wordEnd(0), temp(0){}
    ~NFAs() {wordStart = wordEnd = temp = 0;}

    int compute();      int getPreProc();
    int getFunc();      int getEntrScope();
    int getVoid();      int getInt();
    int getReturn();    int getArgs();
    int getScope();     int getExtScope();

    void setWordStart(char * front, char * end) {wordStart = front; wordEnd = end;}

private:
    char * wordStart;   char * wordEnd;
    char * temp;
};

#endif
