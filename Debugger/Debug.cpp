#include "../Headers/All.h"

#include    <iostream>

std::unordered_map<std::string_view, scp *> Scopes;
std::unordered_map<std::string_view, func *>  Functions;

Scanner * s = new Scanner("../Tests/test1.txt");
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
    freopen("../Output/out1.txt", "w", stdout);
    func * f = newFunc("printf(");
    std::cout << "START" << '\n';
    Functions.insert( {"printf(", f} );
    p->parse();

    fclose(stdout);
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