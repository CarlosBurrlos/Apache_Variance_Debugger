#include    <iostream>
#include    "NFAs.cpp"
#include    "Scanner.cpp"
#include    "Parser.cpp"

using namespace Dbugr;

int main() {

    Scanner* s = new Scanner("../tmp.txt");

    s->readLine();

    /* Psuedo Code
     *  while (1) {
     *      Scanner->readWord();
     *
     *  }
     */


    /*

    NFAs * nfa = new NFAs();
    char * test = const_cast<char *> ("#include");
    nfa->setWordStart(test);

    if(nfa->compute() == PREPROC) {
        std::cout << "TEST PASS" << '\n';
    }
*/

    /*Scanner * s = new Scanner("../tmp.txt");
    s->readWord();
    size_t len = s->getCurrStrSize();
    std::string_view sub(s->getWordStart(), len);*/
    return 0;
}