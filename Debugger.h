/**
 * Debugger tool Prototype:w
 **/
//#include    "ctre.hpp"
#include    "tokens.h"

#include    <iostream>
#include    <fcntl.h>
#include    <sys/stat.h>
#include    <sys/mman.h>

#include    <unordered_map>
#include    <unordered_set>

namespace Dbugr {

    class Parser;
    class Scanner;
    class Scope;
    class Func;

    std::unordered_map<std::string/*scpName*/, Scope *> allScopes;
    std::unordered_map<std::string/*Name*/,Func *> allFuncs;

    class Scanner {

        friend class Dbugr::Parser;

        public:

            explicit Scanner(const char * file);
            ~Scanner();

            char getCurrChar();        char * getWordStart();
            int readChar();            int readWord();
            int readTill(char);        int currStrCmp(char *);
            int printCurrStr();        int getCurrStrSize();

        private:
            int        wf_idx;         int             we_idx;
			int		   fileDescpt;     int 			   fIdx;
			int		   eofIdx;
			bool       nuWord;         bool            atEnd;

			char *	   file;           char **      currWord;
    };

    class Parser {

        public:
                Parser(){}
                ~Parser(){}

                void parse();            void parseWord();
                void parsePreProc();     bool parsePreProcPrime();
                void parseProto();       void parseFunc(); //TODO::Change args to void
                bool parseFuncBody();    bool parseFuncCall();

                int consume();

                std::unordered_set<char*> parseArgs();

            private:
                void enterScope(Scope *);       void exitScope();

                Scope * scope;                    Scanner * scanner;
                bool checkAndConsume(std::__1::basic_regex<char>);
                bool check(std::__1::basic_regex<char>);
    };

    class Scope {
        public:
            Scope(char * name)
            :nFuncOccurs(0), scopeArgs(nullptr),
             scopeName(name),retType(nullptr),
             isScope(0) {}

            ~Scope() {
                this->nFuncOccurs = 0;
                scopeArgs = nullptr;
                scopeName = nullptr;
                retType = nullptr;
                isScope = 0;
            }
            char * getScope() {
                return this->scopeName;
            }
            char * getRetType() {
                return this->retType;
            }
            char * getScopeArgs() {
                return this->scopeArgs;
            }
            void addFunc(std::pair <std::string, Func*> p) {
                this->funcs.insert(p);
            }
            bool contains(std::string s) {
                std::unordered_map<std::string, Func*>::const_iterator i =
                        this->funcs.find(s);
                if (i == this->funcs.end())
                    return 0;
                return 1;
            }
            void set() {
                this->isScope = !(this->isScope);
            }
            bool hasFunc(char * func) {
                return (funcs.find(func) == funcs.end());
            }

        private:
            int nFuncOccurs;
            char * scopeArgs;           char * scopeName;
            char * retType;
            bool isScope;
            std::unordered_map<std::string/*funcName*/, Func *> funcs;
    };

    class Func {
        public:
            Func(char * name)
            :nFuncOccurs(0), funcArgs(nullptr),
            funcName(name),  isFuncCall(0){}

            ~Func()
            {
                nFuncOccurs = 0;        isFuncCall = 0;
                funcArgs = nullptr;     funcName = nullptr;
            }

            char * getName() {
                return this->funcName;
            }
            char * getArgs() {
                return this->funcArgs;
            }
            int getNOccurs() {
                return this->nFuncOccurs;
            }
            void set() {
               this->isFuncCall = !(this->isFuncCall);
            }

        private:

            int nFuncOccurs;
            char * funcArgs;        char * funcName;
            bool isFuncCall;
    };
    class Errors{
        //TODO:: construct an error class that will allow us to throw -> STDERR
        //Question to consider, do we want to output to a file or just to STDOUT
    };
}
