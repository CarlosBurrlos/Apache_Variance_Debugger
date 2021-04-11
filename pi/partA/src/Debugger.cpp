#include "../include/Globals.h"
#include "../include/Scanner.h"
#include "../include/Parse.h"

#include <iostream>

int T_SUPPORT;
double T_CONFIDENCE;


std::unordered_map<std::string_view, scp *> Scopes;
std::unordered_map<std::string_view, func *>  Functions;

Scanner * s;
Parse * p;

const char * _illegal_usage = "Debug: illegal usage";
const char * _input_file_format = "Input Format: \t[\"*.txt\"]";
const char * usage = "Usage: Debug [\"File Name\"]";

void    __usage(int, char **);

int main(int argc, char * argv[]) {

    if (argc <= 1 || argc > 4) {
        __usage(argc, argv);
        return -1;
    }

    s = new Scanner(argv[1]);
    p = new Parse(s);

    if (argc < 4) {
        T_SUPPORT = 3;
        T_CONFIDENCE = 65;
    } 
    else {
        T_SUPPORT = atoi(argv[2]);
        T_CONFIDENCE = atoi(argv[3]);
    }
//    while (s->readWord()) ;
    p->parse();
    return 0;
}

void __usage(int argc, char ** argv) {
    std::cout << "I----------------------------------------------------------I" << '\n';
    std::cout << "  " << _illegal_usage << "   >> " << _input_file_format << '\n';
    std::cout << "  " << usage << "     . . ." << '\n';
    std::cout << "I----------------------------------------------------------I" << '\n';
}
