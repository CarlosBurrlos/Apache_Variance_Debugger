#ifndef INC_408DEBUGGER_SCANNER_H
#define INC_408DEBUGGER_SCANNER_H

class Scanner {

    friend class Parser;

public:

    explicit Scanner(const char * file);
    ~Scanner();

    [[maybe_unused]] char getCurrChar();        char * getWordStart();
    int readChar();            int readWord();
    static int readTill([[maybe_unused]] char);

    [[maybe_unused]] int currStrCmp(char *);

    [[maybe_unused]] int printCurrStr();        int getCurrStrSize() const;
    int readLine();

private:

    int        wf_idx;         int             we_idx;
    int		   fileDescpt;     int 			   fIdx;
    int		   eofIdx;

    bool       nuWord;         bool            atEnd;
    bool       nuLine;

    char *	   file;           char **      currWord;

    NFAs *      nfa;
};

#endif //INC_408DEBUGGER_SCANNER_H
