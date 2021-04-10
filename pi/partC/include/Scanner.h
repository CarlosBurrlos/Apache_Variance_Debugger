#ifndef INC_408DEBUGGER_SCANNER_H
#define INC_408DEBUGGER_SCANNER_H
#include "../include/NFAs.h"

#include <string_view>

#define ENDWORD     -2
#define OK           1
#define STARTWORD    2
#define END          3


class Scanner {
    friend class Parse;
public:
    explicit Scanner(const char * file);
    ~Scanner();
    int readChar();            int readWord();
    int getSize() {return (we_idx - wf_idx + 1);}
    char * getCurrWrdPtr() {return &file[wf_idx];}
    int readLine();
    int readTill(char);
    std::string_view getCurrStr()
        {return std::string_view (&file[wf_idx], (we_idx - wf_idx) + 1);}

private:
    int        wf_idx;         int             we_idx;
    int		   fileDescpt;     int 			   fIdx;
    int		   eofIdx;
    bool       nuWord;         bool            atEnd;
    char *	   file;           char            currChar;
    std::string_view word;
    NFAs *      nfa;
};

#endif //INC_408DEBUGGER_SCANNER_H
