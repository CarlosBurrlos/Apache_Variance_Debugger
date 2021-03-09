/**
 * Debugger tool Prototype:w
 **/
#include    "Results.h"

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
            std::ifstream  in;
    };

    class Parser {

        //What do we need for the parser?

        public:
            Parser(Scanner * s)
            :scanner(s)
            {  }

            ~Parser();  //TODO
            //Checks scanners curr str type & parses
            void parse();
            //Creates new function, adds to set
            void parseFunc(std::string);
            //Creates new scope, adds to set
            void parseScope(std::string);
            //Completes curr scope and exits
            void done();

        private:

            Scope * enterNScope(std::string name);

            void exitScope();

            void addNScope();

            void addNFun();

            void checkIfParsed();

            Scope * scp;

            Scanner * scanner;
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
        private:
            std::unordered_map<std::string, Func*> funcs;
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
            std::string name;
    };

    class Debugger {
        friend class Scanner;
        
        public:

        private:
            //char buff [50];
            //char errBuff [100];
    };
}
