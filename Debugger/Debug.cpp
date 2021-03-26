#include "../Headers/All.h"
#include "../Headers/NFAs.h"

#include    <iostream>

Scanner * s = new Scanner("../Tests/test0.txt");
Parser * p = new Parser(s);

const char * _illegal_usage = "Debug: illegal option";
const char * usage = "usage: Debug [(FILE_NAME)]";

void    __usage(int, char **);

int main(int argc, char * argv[]) {
    /*
    if (argc == 0 || argc > 1) {
        __usage(argc, argv);
        return -1;
    }
    */

    while (s->readWord() != END) {
        //p->parse();
    }

    /*Debugging*/
    /*
    std::string_view debug_str;
    auto *s = new Scanner("../Tests/test1.txt");
    while (1) {
        if (s->readWord() == 3)
            break;
    }
    */

    return 0;
}

void __usage(int argc, char ** argv) {
    std::cout << _illegal_usage << ' ';
    for (; argc > 0; argc--) {
        std::cout << argv[argc];
    }
    std::cout << '\n';
    std::cout << usage << '\n';
}