#include <iostream>
#include "Debugger.h"
#include "Scanner.cpp"

using namespace Dbugr;
int main() {
    auto *s = new Scanner("tmp.txt");
    s->openStream();
    s->nextChar();
    printf("%s\n", s->getCurrChar());
    s->closeStream();
    return 0;
}
