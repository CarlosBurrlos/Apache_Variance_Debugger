#include "../include/NFAs.h"

#define a_z(c) ({\
    bool ret;                 \
    ( (c >= 65 && c <= 90) || \
      (c >= 97 && c <= 122))  \
      ? ret = true : ret = false; \
      ret;\
    })

#define a_z_0_9(c) ({ \
    bool ret;                 \
    ( (c >= 65 && c <= 90)  ||\
      (c >= 97 && c <= 122) ||\
      (c >= 48 && c <= 57))   \
      ? ret = true : ret = false; \
      ret;\
})

#define _0_9(ptr) ({ \
bool ret;              \
(*(ptr) >= 48 && *(ptr) <= 57)\
    ? ret = 1 : ret = 0;      \
ret;\
})

int NFAs::compute() {
    if (getScopeNode())
        return SCOPENODE;
    else if (getScope())
        return SCOPE;
    else if (getNullFunc())
        return NULLFUNC;
    else if (getMain())
        return MAIN;
    else if (getPrintf())
        return PRINTF;
    else if (getFuncNode())
        return FUNCNODE;
    else if (getFuncName())
        return FUNC;
    else if (getFuncAddr())
        return FUNCADDR;
    else if (getUses())
        return USES;
    return BAD;
}

int NFAs::getScope() {
    temp = wordStart;
    if (*(temp) != 's')  return 0; temp++;
    if (*(temp++) != 'c') return 0;
    if (*(temp++) != 'o') return 0;
    if (*(temp++) != 'p') return 0;
    if (*(temp++) != 'e') return 0;
    while (temp < wordEnd) {
        temp++;
    }
    if (temp != wordEnd) return 0;
    return 1;
}

int NFAs::getScopeNode() {
    temp = wordStart;
    if (*(temp) != 's')  return 0; temp++;
    if (*(temp++) != 'c') return 0;
    if (*(temp++) != 'o') return 0;
    if (*(temp++) != 'p') return 0;
    if (*(temp++) != 'e') return 0;
    while (temp < wordEnd) {
        temp++;
    }
    if (temp != wordEnd) return 0;
    if (*(temp + 2) != '<') return 0;
    return 1;
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
    if (!a_z(*temp))    return 0;
    while (temp != wordEnd) {
        if (!a_z(*temp) && *temp != ' ') { return 0; }
        temp++;
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
    if (!a_z(*temp))    return 0;
    while (temp != wordEnd) {
        if (!a_z(*temp) && *temp != ' ') { return 0; }
        temp++;
    }
    return 1;
}

int NFAs::getUses() {
    temp = wordStart;
    if (!_0_9(temp)) return 0;
    while (temp != wordEnd) {
        if (!_0_9(temp)) return 0;
        temp++;
    }
    return 1;
}

int NFAs::getFuncAddr() {
    temp = wordStart;
    if (!a_z_0_9(*temp)) return 0;
    if (*++temp != 'x') return 0;
    if (!a_z_0_9(*++temp)) return 0;
    return 1;
}