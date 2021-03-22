#ifndef INC_408DEBUGGER_SCANNER_H
#define INC_408DEBUGGER_SCANNER_H


class Scanner {

    friend class Parser;

public:

    explicit Scanner(const char * file);
    ~Scanner();

    int readChar();            int readWord();
    int getCurrStrSize() const;
    int readLine();

    std::string_view getCurrStr()
        {return std::string_view (&file[wf_idx], (we_idx - wf_idx));}

private:

    int        wf_idx;         int             we_idx;
    int		   fileDescpt;     int 			   fIdx;
    int		   eofIdx;

    bool       nuWord;         bool            atEnd;
    bool       nuLine;

    char *	   file;

    std::string_view word;

    NFAs *      nfa;
};

#endif //INC_408DEBUGGER_SCANNER_H
