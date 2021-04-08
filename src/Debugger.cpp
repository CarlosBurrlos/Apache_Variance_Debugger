#include "../include/Globals.h"
#include "../include/Scanner.h"
#include "../include/Parser.h"

#include <iostream>

int T_SUPPORT;
double T_CONFIDENCE;


std::unordered_map<std::string_view, scp *> Scopes;
std::unordered_map<std::string_view, func *>  Functions;

Scanner * s;
Parser * p;

const char * _illegal_usage = "Debug: illegal usage";
const char * _input_file_format = "Input Format: \t[\"*.txt\"]";
const char * usage = "Usage: Debug [\"File Name\"]";

void    __usage(int, char **);

int main(int argc, char * argv[]) {

    s = new Scanner("/Users/carlos/Desktop/__/School/2021/CS408/408Debugger/cw.txt");
    while (s->readWord() != END) {
        std::cout << s->getCurrStr();
        std::cout << "    " << Token << '\n';
    }

    /*
    if (argc <= 1 || argc > 4) {
        __usage(argc, argv);
        return -1;
    }

    //file n x
    //output = test

    s = new Scanner(argv[1]);
    p = new Parser(s);

    if (argc < 4) {
        T_SUPPORT = 3;
        T_CONFIDENCE = 65;
    } 
    else {
        T_SUPPORT = atoi(argv[2]);
        T_CONFIDENCE = atoi(argv[3]);
    }
    
    func * f = newFunc("printf");
    auto n_func = std::make_pair("printf", f);
    Functions.insert(n_func);
    p->parse();
    return 0;
    */
}

void __usage(int argc, char ** argv) {
    std::cout << "I----------------------------------------------------------I" << '\n';
    std::cout << "  " << _illegal_usage << "   >> " << _input_file_format << '\n';
    std::cout << "  " << usage << "     . . ." << '\n';
    std::cout << "I----------------------------------------------------------I" << '\n';
}
