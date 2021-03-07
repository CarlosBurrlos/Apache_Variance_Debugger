#include "Scnr_P.h"
#include <istream>
#include <fstream>

int main() {

    int n = 0;

    std::ifstream in;
    in.open("test.txt");
    if (in.is_open())
        printf("%c\n", in.get());
    /*
    Scnr *s;
    s = new Scnr("/Users/carlos/Documents/Docs-R/School/2021/CS408/beta/Prototyping/test.txt");
    s->openFile();
    for(int i = 0; i < 7; i++) {
        s->nxtChar();
        printf("%c", s->getCurrChar());
    }
    n = s->getNBytes();
    s->closeFile();
     */
    return n;
}

