#include    <iostream>
#include    "Scanner.cpp"
#include    "Parser.cpp"
#include    "ctre.hpp"

using namespace Dbugr;

int main() {

    Scanner * s = new Scanner("../tmp.txt");

    s->readWord();
    size_t len = s->getCurrStrSize();
    std::string_view sub(s->getWordStart(), len);
    if (auto m = ctre::match<"[a-z]+)">(sub)) {

    }

    return 0;
}