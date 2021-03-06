/**
 * Debugger tool Prototype:w
 **/

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

            Parser();
            ~Parser();

            void parseFunc();

            void parseScope();

            void done();

        private:
            void enterNScope();
            void exitScope();
            void addNScope();
            void addNFun();
            void checkIfParsed();
            Scope * scp;
    };
    
    //Might not need this
    class MasterScope{    };

    class Scope {
        public:
            Scope(char * name) 
            : name(name)
            {}
            ~Scope() 
            {} //TODO
            std::string getScope() {
                return this->name;
            }
        private:
            std::unordered_map<std::string, Func*> funcs;
            char * name;
    };

    class Func {
        public:
            Func(char * name)
                :name(name)
            {}
            ~Func()
            {} //TODO
            char * getFunc() {
                return this->name;
            }
        private:
            char * name;
    };

    class Debugger {
        friend class Scanner;
        
        public:

        private:
            //char buff [50];
            //char errBuff [100];
    };
}
