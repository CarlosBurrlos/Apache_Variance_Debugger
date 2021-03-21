#include    "NFAs.h"
#include    "Scanner.h"

#include    <iostream>
#include    <fcntl.h>
#include    <sys/stat.h>
#include    <sys/mman.h>

#include    <unordered_map>
#include    <unordered_set>

const char * SEMICOL         = ";";
const char * LPAREN          = "(";
const char * RPAREN          = ")";
const char * POUND           = "#";
const char * COM             = ",";
const char * NLINE           = "\n";
const char * TAB             = "\\t";
const char * SPACE           = " ";
const char * MAIN            = "main";
const char * LBRACKET        = "{";
const char * RBRACKET        = "}";
const char * INCLUDE         = "include";
const char * DEFINE          = "define";
const char * PROC            = "#(include|define)";


class Parser;
class Scanner;
class Scope;
class Func;

std::unordered_map<std::string_view/*scpName*/, Scope *> allScopes;
std::unordered_map<std::string_view/*Name*/,Func *> allFuncs;

static int Token;

//    class Scanner {
//
//        friend class Dbugr::Parser;
//
//        public:
//
//            explicit Scanner(const char * file);
//            ~Scanner();
//
//        [[maybe_unused]] char getCurrChar();        char * getWordStart();
//            int readChar();            int readWord();
//            static int readTill([[maybe_unused]] char);
//
//        [[maybe_unused]] int currStrCmp(char *);
//
//        [[maybe_unused]] int printCurrStr();        int getCurrStrSize() const;
//            int readLine();
//
//        private:
//
//            int        wf_idx;         int             we_idx;
//			int		   fileDescpt;     int 			   fIdx;
//			int		   eofIdx;
//
//			bool       nuWord;         bool            atEnd;
//			bool       nuLine;
//
//			char *	   file;           char **      currWord;
//
//			NFAs *      nfa;
//    };



class Errors{
        //TODO:: construct an error class that will allow us to throw -> STDERR
        //Question to consider, do we want to output to a file or just to STDOUT
};
