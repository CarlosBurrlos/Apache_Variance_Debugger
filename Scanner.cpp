#include "Header.h"

#include <regex>

using namespace Dbugr;

Scanner::Scanner(const char * file)
:   c(NULL),
    cStr(NULL),
    file(file),
    currStrType(0)
{
   freopen(file, "r", stdin);
}

Scanner::~Scanner() {
   fclose(stdin);
}

/**
 *  Calls private method r() which reads a char from
 *  field file ifstream
 **/
int Scanner::read() {
    int charsRead = 0;
    charsRead = r();
    return charsRead;
}

/**
 *  int readNChars()
 **/
int Scanner::readNChars(int N){
    int charsRead = 0;
    for (; charsRead < N && read(); charsRead++)
        ;
    (charsRead == N) ? : charsRead = -1;
    return charsRead;
}

/**
 *  int readFunc()
 **/
int Scanner::readFunc() {
    int charsRead = readTill(';');
    r();
    charsRead++;
    return charsRead;
}

/**
 *  int readLine()
 **/
int Scanner::readLine() {
    int charsRead = 0;
    while ((charsRead = r())) {
        charsRead ++;
        if (*getCurrChar() == '\n')
            break;
    }
    return charsRead;
}

/**
 *  int readTill()
 **/
int Scanner::readTill(char c) {
    bool read = 0;
    if (c != ';' || c != '{' || c != '}')
        return -1;
    int charsRead = 0;
    while ((charsRead = r())) {
        if (*getCurrChar() == c) {
            read = 1;
            break;
        }
        if (*getCurrChar() == ';' && c != ';') {
            ;//TODO:: err
        }
        if ((*getCurrChar() == '{' || *getCurrChar() == '}') &&
                (*getCurrChar() == ';')) {
            ;//TODO:: err
        }
        charsRead++;
    }
    if (!read) {
        //TODO:: no c 
    }
    return charsRead;
}

/**
 *  bool hasChar()
 **/
bool Scanner::hasChar() {
    return atEnd();
}

/**
 *  int r()
 **/
int Scanner::r() {
    char c = '0'; 
    c = getchar_unlocked();
    
    if(c == EOF) {
        this->end = true;
        return EOFERR;
    }

    this-> c = &c; 
    this->cStr+= c;
    return 1;
}

int Scanner::setcurrStrType() {
    int i = 0;
    for (std::regex r : regs) {
        if (regex_match(this->cStr, r)) {
            this->currStrType = i;    
        }
        i++;
    }
    return 0;
}
