#include "Header.h"

#include <regex>

using namespace Dbugr;

Scanner::Scanner(const char * file)
:   c(NULL),
    file(file),
    cStr(NULL)
{}

Scanner::~Scanner() {
    close();
}

bool Scanner::openStream() {
    if (open())
        return 1;
    return 0;
}

bool Scanner::closeStream() {
    if (close())
        return 1;
    return 0;
}

/*
 * Reads a char from Scanners ifstream (file)
 * Returns 1 if char was read successfully
 * Returns 0 otherwise
 */
int Scanner::nextChar() {
    if (readChar()) return 1;
    return 0;
}

/*
 * Reads in a line from Scanners ifstream (file)
 * Returns n chars successfully read
 * Returns 0 if no chars read
 */
int Scanner::nextLine() {
    int n = 0;
    if ((n = readLine())) return n;
    return n;
}

/*
 * Reads in next word from Scanners ifstream (file)
 * Returns n chars successfully read
 * Returns 0 if no chars read
 */
int Scanner::nextWord() {
    int n = 0;
    if ((n = readWord())) return n;
    return n;
}

/*
 * Reads till specified char
 * Returns n chars successfully read
 * Returns 0 otherwise
 */
int Scanner::scanTill(char c) {
    int n = 0;
    if ((n = readTill(c)))
        return n;
    return n;
}

/*
 *
 */
int Scanner::nextFunc() {
    int n = 0;
    if ((n = readTill(';')))
        return n;
    return n;
}

/*
 * Checks if the ifstream has just read a char
 * If it has read EOF or Failed to read ('^')
 * then return False.
 * Else, return True.
 */
bool Scanner::hasChar() {

    if ((*this->getCurrChar() == EOF) ||
        (*this->getCurrChar() == '^') ||
        (!this->getCurrChar()))
        return 0;
    return 1;
}

/*
 * [Private] Reads in char from ifstream (file)
 * Checks the EOF or Fail bits. If failed to read
 * then return -1
 * Else, return 1
 */
int Scanner::readChar() {
    if (readCheck() != 1)
        return -1;
    *this->c = in.get();
    if (this->in.fail()) {
        *this->c = '^';
        this->in.clear();
        return -1;
    }
    else if (this->in.eof()) {
        *this->c = EOF;
        this->in.clear();
        return -1;
    }
    return 1;

}

/*
 * [Private] Safer method for reading in char
 * firom ifstream. First peeks if the stream
 * has char.
 * Returns 1 if peek and read
 * else returns -1
 */
int Scanner::readCheck() {
    char c = this->in.peek();
    if (c == EOF) {
        return -1;
    }
    if (c == '^') {
        return -2;
    }
    //TODO
    return 1;
}

/*
 * [Private] Reads in line from ifstream (file)
 * Returns -1 if EOF or Failure
 * Returns n chars read from ifstream
 */
int Scanner::readLine() {

    int n = 0;
    if (readCheck())
        readChar();
    while ((*this->c != '\n') &&
            ((*this->c != '^') ||
              (*this->c != EOF)))
    {
        readChar();
        n++;
    }
    n--;
    if ((*this->c == '^') ||
            (*this->c == EOF)) {
        return -1;
    }
    return 1;

}

/*
 * [Private] Reads in a word from ifstream (file)
 * Returns -1 if EOF or Failure
 * Returns n chars read
 */
int Scanner::readWord() {
    
    int n = 0;
    if (readCheck())
        readChar();
    while ((*this->c != ' ') || (*this->c != '\n') ||
          (*this->c != '\t') || (*this->c != '^') ||
          (*this->c != EOF))
    {
        readChar();
        n++;
    }
    n--;
    if ((*this->c == '^') ||
            (*this->c == EOF))
        return -1;
    return n;
}

/*
 * [Private] Reads till a certain char
 * Returns -1 if EOF or Failure
 * Returns n chars read
 */
int Scanner::readTill(char cc) {
    int n = 0;
    if (readCheck())
        readChar();
    while ((*this->c != cc) || (*this->c != '^') ||
          (*this->c != EOF))
    {
        readChar();
        n++;
    }
    return n;
}
