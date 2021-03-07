#include <ostream>
#include <cstdio>
#include <istream>

class Scnr {
    public:
        Scnr(char * c)
            : file(c)
        {}
        ~Scnr() {
            this->file = NULL;
        }

        int openFile();     //(Success) ? 1 : -1
        static int closeFile();    //(Success) ? 1 : -1

        int nxtChar();      //(Success) ? 1 : 0
        int nxtStrng();     //(Success) ? nChars Read : -1
        int nxtLine();      //(Success) ? nChars Read : -1

        char getCurrChar() {
            return this->currChar;
        }

        std::string getCurrStr() {
            return this->currStr;
        }
        int getNBytes() {
            return this->nBytes;
        }

    private:

        void clearBytes();
        void updateBytes();

        int open();
        static int close();
        int readChar();
        int readStr();
        int readLine();

        int nBytes{};
        int gBytes{};
        
        char currChar{};
        char * file;

        std::istream in;

        std::string currStr;
        
};



