#include "../include/NFAs.h"

bool is_0_9 (char c) {
    if ( c >= 48 && c <= 57) return true;
    return false;
}

bool is_a_z_0_9 (char c) {
    if (c >= 65 && c <= 90) return true;
    if (c >= 97 && c <= 122) return true;
    if (c >= 48 && c <= 57)  return true;
    return false;
}

bool is_a_z(char c) {
    if (c >= 65 && c <= 90) return true;
    if (c >= 97 && c <= 122) return true;
    return false;
}


int NFAs::compute() {
    if (getNullFunc())
        return NULLFUNC;
    else if (getMain())
        return MAIN;
    else if (getPrintf())
        return PRINTF;
    else if (getFuncNode())
        return FUNCNODE;
    else if (getFuncAddr())
        return FUNCADDR;
    else if (getFuncName())
        return FUNC;
   else if (getUses())
        return USES;
    return BAD;
}

int NFAs::getNullFunc() {
    temp = wordStart;
    if (*temp != 'n') return 0;
    temp++;
    if (*temp++ != 'u') return 0;
    if (*temp++ != 'l') return 0;
    if (*temp++ != 'l') return 0;
    if (*temp++ != ' ') return 0;
    if (*temp++ != 'f') return 0;
    if (*temp++ != 'u') return 0;
    if (*temp++ != 'n') return 0;
    if (*temp++ != 'c') return 0;
    if (*temp++ != 't') return 0;
    if (*temp++ != 'i') return 0;
    if (*temp++ != 'o') return 0;
    if (*temp != 'n') return 0;
    return 1;
}

int NFAs::getFuncNode() {
    temp = wordStart;
    if (is_a_z_0_9(*temp) || *temp == '.' || *temp == '_'){ temp++;}
    else {return 0;}
    while (temp != wordEnd) {
        if (is_a_z_0_9(*temp) || *temp == '.' || *temp == '_') { temp++; }
	else return 0;
    }
    if (*(temp + 2) == '<') return 1;
    return 0;
}

int NFAs::getPrintf() {
    temp = wordStart;
    if (*temp != 'p') return 0;
    temp++;
    if (*temp++ != 'r') return 0;
    if (*temp++ != 'i') return 0;
    if (*temp++ != 'n') return 0;
    if (*temp++ != 't') return 0;
    if (*temp != 'f') return 0;
    return 1;
}

int NFAs::getMain() {
    temp = wordStart;
    if (*temp != 'm') return 0;
    temp++;
    if (*temp++ != 'a') return 0;
    if (*temp++ != 'i') return 0;
    if (*temp != 'n') return 0;
    return 1;
}

int NFAs::getFuncName() {
    temp = wordStart;
    if (is_a_z_0_9(*temp) || *temp == '.' || *temp == '_'){ temp++;}
    else {return 0;}
    while (temp != wordEnd) {
        if (is_a_z_0_9(*temp) || *temp == '.' || *temp == '_'){ temp++;}
	else return 0;
    }
    return 1;
}

int NFAs::getUses() {
    temp = wordStart;
    if (!is_0_9(*temp)) return 0;
    while (temp != wordEnd) {
        if (!is_0_9(*temp)) return 0;
        temp++;
    }
    return 1;
}

int NFAs::getFuncAddr() {
    temp = wordStart;
    if (!is_0_9(*temp)) return 0;
    if (*++temp != 'x') return 0;
    if (!is_a_z_0_9(*++temp)) return 0;
    return 1;
}
