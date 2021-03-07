#include "Scnr_P.h"
#include <cstdio>

#define EOFerr      -1
#define READerr     -2

int Scnr::openFile() {
    return open();
}

int Scnr::closeFile() {
    if (close() == EOF) return -1;
    return 1;
}

int Scnr::nxtChar() {
    return readChar();
}

int Scnr::nxtStrng() {
    return readStr();
}

int Scnr::nxtLine() {
    return 0;
}

void Scnr::clearBytes() {
    this->nBytes = 0;
}

int Scnr::open() {
    FILE * f = freopen(this->file, "r", stdin);
    if (!f) return -1;
    return 1;
}

int Scnr::close() {
    return fclose(stdin);
}

int Scnr::readChar() {
    char c = getchar_unlocked();
    if (c == EOF) {
        int retval = 0;
        if (feof(stdin)) {
            printf("EOF Reached\n");
            retval = EOFerr;
        }
        else if (ferror(stdin)) {
            printf("ERR Reading From File ||%s||\n", this->file);
            retval = READerr;
        }
        printf("Total Number of Bytes Read:\n");
        printf("||%d||", this->nBytes);
        return retval;
    }
    this->currChar = c;
    this->nBytes++; this->gBytes+=this->nBytes;
    return 1;
}

int Scnr::readStr() {
    clearBytes();
    while (((this->currChar != EOF)      ||
            (this->currChar != '\n')    ||
            (this->currChar != ' '))   &&
            (readChar() == 1))    
    {
        this->currStr += this->currChar;
    }
    return this->nBytes;
}
