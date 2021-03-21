#include "../Headers/All.h"



void    __usage();

int main(int argc, char * argv[]) {

    if (argc == 0 || argc > 1) {
        __usage();
    }

    auto *s = new Scanner("../tmt.txt");
    s->readWord();

    return 0;
}

void __usage() {


}