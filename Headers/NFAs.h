#ifndef INC_408DEBUGGER_NFAS_H
#define INC_408DEBUGGER_NFAS_H

#define BAD     0
#define PREPROC 1
#define FUNC    2
#define SCOPE   3
#define RETVOID 4
#define RETINT  5
#define RETRN   6

class NFAs {
public:

    NFAs(): wordStart(nullptr){}
    ~NFAs() {if (wordStart) wordStart = nullptr;}

    int compute();      int getPreProc();
    int getFunc();      int getScope();
    int getVoid();      int getInt();
    int getReturn();

    void setWordStart(char * ptr) {wordStart = ptr;}

private:
    char * wordStart;
};

#endif