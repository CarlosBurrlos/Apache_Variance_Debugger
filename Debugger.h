/**
 * Debugger tool Prototype:w
 **/
#include    "Results.h"

#include    <stdio.h>
#include    <ostream>
#include    <fstream>
#include    <unordered_map>

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

            //Construct
            Scanner(const char * file);
            //Destruct
            ~Scanner();

            //Gets current character
            char * getCurrChar() {
                return this->c;
            }

            //Gets current string
            std::string getCurrStr() {
                return this->cStr;
            }

            //Gets name of filed being read
            std::string getFile() {
                return this->file;
            }

            int getCurrType() {
                return this->currStrType;
            }

            bool atEnd() {
                return this->end;
            }

            //Reads in chars
            int read();

            //Reads in N chars
            int readNChars(int);

            //Reads in stream till ';'
            int readFunc();

            //Reads complete line
            int readLine();

            //Read till char
            int readTill(char);

            //ifstream has char
            bool hasChar();

        private:
            
            //Prvt methods for reading
            int r();
        
            int setcurrStrType();
            
            //Private fields
            char*           c;
            std::string     cStr;
            const char *    file;
            int             currStrType;
            bool            end;

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

            Scope * enterNScope();

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
