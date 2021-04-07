#include "../include/Globals.h"
#include "../include/Scanner.h"
#include "../include/Parser.h"

#include <iostream>

std::unordered_map<std::string_view, scp *> Scopes;
std::unordered_map<std::string_view, func *>  Functions;

Scanner * s;
Parser * p;

const char * _illegal_usage = "Debug: illegal usage";
const char * _input_file_format = "Input Format: \t[\"*.txt\"]";
const char * usage = "Usage: Debug [\"File Name\"]";

void    __usage(int, char **);

int main(int argc, char * argv[]) {
    /*
    if (argc <= 1 || argc > 2) {
        __usage(argc, argv);
        return -1;
    }
    */
    //s = new Scanner(argv[1]);
    s = new Scanner("/Users/carlos/Desktop/__/School/2021/CS408/408Debugger/tests/test2.txt");
    p = new Parser(s);
    func * f = newFunc("printf");
    auto n_func = std::make_pair("printf", f);
    Functions.insert(n_func);
    p->parse();
    return 0;
}

void __usage(int argc, char ** argv) {
    std::cout << "I----------------------------------------------------------I" << '\n';
    std::cout << "  " << _illegal_usage << "   >> " << _input_file_format << '\n';
    std::cout << "  " << usage << "     . . ." << '\n';
    std::cout << "I----------------------------------------------------------I" << '\n';
}