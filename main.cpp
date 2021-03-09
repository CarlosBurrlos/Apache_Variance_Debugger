#include    <iostream>
#include    "Debugger.h"
#include    "Scanner.cpp"
#include    "Parser.cpp"
#include    "Expressions.h"

#define     SCNFAILURE  -4

void readEmptyLines();
void consumeProtos();

using namespace Dbugr;
Scanner * s = new Scanner("");
Parser  * p = new Parser(s);
int main() {
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
    return 0;
}

void run() {
    //first check if there is anything to read
    if (s->peekChar() != EOF) {
        //First we want to read the includes or defines
        while (s->nextWord() &&
               std::regex_match(s->getCurrStr(),incOrDefRegx))
        {
            s->nextLine();
            //There could possibly be empty lines interspersed
            readEmptyLines();
        }
        //Read Lines before reading protos
        readEmptyLines();
        //Consume our protos
        consumeProtos();
        //Read Empty lines
        readEmptyLines();
        while (s->peekChar() != EOF) {
            //Now we being reading our actual file

        }
    }
    printf("EOF REACHED::%d-CHARS READ\n", s->getNCharsRead());
}

void readEmptyLines() {
    while (s->peekChar() == '\n')
        s->nextLine();
}

void consumeProtos() {
        while (1) {
            if (s->peekChar() == '\n') break;
            //Grab "void"
            s->nextWord();
            //Grabe "scope..."
            s->nextLine();
            if (std::regex_match(s->getCurrStr(), scopeProtoRegx)) {
               //TODO Handle the scopes with our parser
               //   >>Create their new entries
            }
            if (std::regex_match(s->getCurrStr(), funcProtoRegx)) {
                //TODO Handle the func with our parser
                //  >>Create new func instance and store
            }
        }
}
