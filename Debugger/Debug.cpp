#include "../Headers/All.h"
#include    <iostream>

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
    /*
    const char * msg = "HELLO";
    int size = strlen(msg);
    std::string_view s_vew(msg, size);
    std::string_view s_vew_2(msg, size);

    std::hash<std::string_view> h;
    std::cout << h(s_vew) << '\n';
    std::cout << h(s_vew_2) << '\n';
    */
    /*
    Func * f = new Func("printf(");
    allFuncs.insert( {"printf(", f} );
    p->parse();

    for (std::pair<std::string_view, Scope*> s_pair : allScopes) {
        std::cout << s_pair.first << '\n';
        for (std::pair<std::string_view, Func*> f_pair : s_pair.second->getFuncs()) {
            std::cout << '\t' << f_pair.first << '\n';
        }
    }

    //What we could do to compute these values
    */
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