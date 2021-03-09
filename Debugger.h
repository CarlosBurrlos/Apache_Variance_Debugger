/**
 * Debugger tool Prototype:w
 **/
#include    <stdio.h>
#include    <ostream>
#include    <fstream>
#include    <unordered_map>
#include    <unistd.h>
#include    <filesystem> //For Debug purposes

namespace Dbugr {

//TODO::Determine errors and create their messages
    
    enum Errs{ E1, E2, E3, E4, E5 };
    const char * errs[] = {
        [E1] = "",
        [E2] = "",
        [E3] = "",
        [E4] = "",
        [E5] = ""
    };

    class Debugger;
    class Scanner;
    class Parser;
    class Scope;
    class Func;

    class Scanner {

        friend class Parser;

        enum Types {
            inScp, leavScp, func, rts, w, parms
        };

        public:

            Scanner(const char * file);
            ~Scanner();

            char getCurrChar() {
                return this->c;
            }
            std::string getCurrStr() {
                return this->cStr;
            }
            int getNCharsRead() {
                return this->glblCharCount;
            }
 
            std::string getFile() {
                return this->file;
            }

            void clearStr() {
                this->cStr.clear();
            }

            bool openStream();
            bool closeStream();
            bool hasChar() const;
            bool atEnd() const {
                return this->eof;
            }
            bool failed() const {
                return this->flr;
            }

            void scan();

            int nextChar();
            int nextLine();
            int nextWord();
            int nextFunc();
            int scanTill(char);
            int peekChar();

        private:

            int open() {
                this->in = std::ifstream(this->file, std::ifstream::in);
                if (in.is_open())
                {return 1;}
                else
                {return 0;}
            }
            
            int close() {
                in.close();
                if (in.is_open()) return 0;
                return 1;
            }

            int readChar();
            int readCheck();
            int readLine();
            int readWord();
            int readTill(char);

            bool           eof;
            bool           flr;

            char           c;

            int             glblCharCount;

            std::string    file;
            std::string    cStr;
            std::string    str;
            std::ifstream  in;
    };

    class Parser {

        //What do we need for the parser?

        public:
            Parser(Scanner * scanner)
            :s(scanner)
            {  }
            ~Parser();
            void parse();
            void parseFunc(std::string,int);
            void readEmptyLines();
            void consumeProtos();

        private:

            void enterScope(Scope *);
            void exitScope();

            Scope *     createScope(std::string);
            Scope *     createMain(std::string);

            bool        nScp;

            Scope * scp;
            Scope * main;
            Scanner * s;
    };
    
    //Might not need this
    class MasterScope{    };

    class Scope {
        public:
            Scope(std::string name) 
            : name(name)
            {}
            ~Scope() 
            {} //TODO
            std::string getScope() {
                return this->name;
            }
            void addFunc(std::pair <std::string, Func*> p) {
                this->funcs.insert(p);
            }
            int contains(std::string s) {
                std::unordered_map<std::string, Func*>::const_iterator i =
                        this->funcs.find(s);
                if (i == this->funcs.end())
                    return 0;
                return 1;
            }

        private:
            bool malformedScope;    //If scope is malformed
            int nCalls;     //Number of calls to this scope
            int nFuncs;     //Number of funcs that called in scope

            std::unordered_map<std::string, Func*>          funcs;

            std::string name;
    };

    class Func {
        public:
            Func(std::string name)
                :name(name)
            {}
            ~Func()
            {} //TODO
            std::string getFunc() {
                return this->name;
            }
        private:
            int nRefs;

            std::string name;
    };
}
