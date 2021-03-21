#include "../Headers/All.h"

#define a_z(c) ({\
    bool ret;                 \
    ( (c >= 65 && c <= 90) || \
      (c >= 97 && c <= 122))  \
      ? ret = true : ret = false; \
      ret;\
    })

#define a_z_0_9(c) ({ \
    bool ret;               \
    ( c >= 65 || c <= 90||  \
      c >= 97 || c <= 122 ||\
      c >= 48 || c <= 57)   \
      ? ret = true : ret = false; \
      ret;\
})



int NFAs::compute() {
    if (getPreProc())
        return PREPROC;
    else if (getFunc())
        return FUNC;
    else if (getScope())
        return SCOPE;
    else if (getVoid())
        return RETVOID;
    else if (getInt())
        return RETINT;
    else if (getReturn())
        return RETRN;
    return BAD;
}

int NFAs::getPreProc() {
    if (*(wordStart) != '#')  return -1;
    wordStart++;
    while (a_z(*wordStart)) {
        wordStart++;
    }
    //Read rest of line automatically
    return 1;
}

int NFAs::getFunc() {
    while (a_z_0_9(*(wordStart))) {
        wordStart++;
    }
    wordStart++;
    if (*(wordStart++) != '(') return -1;
    while (a_z_0_9(*(wordStart++))) ;
    if (*(wordStart++) != ')') return -1;
    if (*(wordStart++) != ';') return -1;
    return 1;
}

int NFAs::getScope() {
    while (a_z_0_9(*(wordStart))) {
        wordStart++;
    }
    wordStart++;
    if (*(wordStart++) != '(') return -1;
    while (a_z_0_9(*(wordStart++))) ;
    if (*(wordStart++) != ')') return -1;
    if (*(wordStart++) != ';') return -1;
    if (*(wordStart++) != ' ')  return 0;
    if (*(wordStart++) != '{')  return 0;
    return 1;
}

int NFAs::getVoid() {
    if (*(wordStart) != 'v')   return -1; wordStart++;
    if (*(wordStart++) != 'o') return -1;
    if (*(wordStart++) != 'i') return -1;
    if (*(wordStart++) != 'd') return -1;
    return 1;
}

int NFAs::getInt() {
    if (*(wordStart) != 'i')   return -1; wordStart++;
    if (*(wordStart++) != 'n') return -1;
    if (*(wordStart++) != 't') return -1;
    return 1;
}

int NFAs::getReturn() {
    if (*(wordStart) != 'r')   return -1; wordStart++;
    if (*(wordStart++) != 'e') return -1;
    if (*(wordStart++) != 't') return -1;
    if (*(wordStart++) != 'u') return -1;
    if (*(wordStart++) != 'r') return -1;
    if (*(wordStart++) != 'n') return -1;
    while (*(wordStart++) != ';') ;
    return 1;
}
