#include    <iostream>
#include    "Scanner.cpp"
#include    "Parser.cpp"
#include    "Invar.cpp"

using namespace Dbugr;
int main() {

    Parser  * p = new Parser();
    Scanner * s = new Scanner("../tmp.txt");
    int start = s->nextWord();
    int end = start + s->getCurrStr();

    /*
    auto *s = new Scanner("tmp.txt");
    if (!s->openStream()) {
        printf("ERR::FAILED TO OPEN %s :: Scanner Failure\n", s->getFile().c_str());
        return SCNFAILURE;
    }
    int n = 0;
    //n = s->nextLine();
    //n = s->nextWord();
    if (n) {
        printf("%d CHARS READ\n", n);
        printf("%s\n", s->getCurrStr().c_str());
        if(s->atEnd()) printf("EOF REACHED\n");
        else if (s->failed()) printf("FAILED TO READ CHAR @ %d + 1\n", n);
    }
    if (!s->closeStream()) {
        printf("ERR::FAILED TO CLOSE %s :: Scanner Failure\n", s->getFile().c_str());
        return SCNFAILURE;
    }
    */

    return 0;
}