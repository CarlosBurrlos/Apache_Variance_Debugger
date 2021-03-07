#include "Scnr_P.h"

int main() {

    char fileName [] = "test.txt";
    int n = 0;
    Scnr * s = new Scnr(fileName);
    s->openFile();
    for(int i = 0; i < 7; i++) {
        s->nxtChar();
        printf("%c", s->getCurrChar());
    }
    n = s->getNBytes();
    s->closeFile();
    return n;
}

