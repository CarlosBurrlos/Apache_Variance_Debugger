#include "../Headers/All.h"

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

#define literal(c) ({ \
    bool ret;         \
    ( (c == 37) ||    \
      (c == 34) ||    \
      (c == 39) ||    \
      (c == 92))      \
      ? ret = true : ret = false; \
})

int NFAs::compute() {
    int check = 0;
    if (getPreProc())
        return PREPROC;
    else if (getScope())
        return SCOPE;
    else if (getFunc())
        return FUNC;
    else if (getArgs())
        return ARGS;
    else if (getEntrScope())
        return ENTR_SCOPE;
    else if (getExtScope())
        return EXT_SCOPE;
    else if (getVoid())
        return RETVOID;
    else if (getInt())
        return RETINT;
    else if (getReturn())
        return RETRN;
    return BAD;
}

//TODO Create a get args

int NFAs::getArgs() {
    temp = wordStart;
    while (1) {
        while ((a_z_0_9(*temp) || literal(*temp))
            && temp <= wordEnd) {
            temp++;
        }
        if (*temp == ',') {
            temp++;
            continue;
        }
        else {
            break;
        }
    }
    if (*temp != ')') return 0;
    return 1;
}

int NFAs::getPreProc() {
    temp = wordStart;
    if (*(temp) != '#' && *(temp) != '"')  return 0;
    temp++;
    while (a_z(*temp) && temp <= wordEnd) {
        temp++;
    }
    if (*(temp) == '"')
        {if (*(temp) != '\n') {return 0;}}
    else if (*(temp) != ' ')
        {return 0;}
    //Read rest of line automatically
    return 1;
}

int NFAs::getFunc() {
    temp = wordStart;
    if (!a_z_0_9(*(temp))) return 0;
    while (a_z_0_9(*(temp)) && temp <= wordEnd ) {
        temp++;
    }
    if (*(temp++) != '(') return 0;
    return 1;
}

int NFAs::getEntrScope() {
    temp = wordStart;
    if (*(temp) == '{')      {return 1;}
    return 0;
}

int NFAs::getExtScope() {
    temp = wordStart;
    if (*(temp) == '}')      {return 1;}
    return 0;
}

int NFAs::getVoid() {
    temp = wordStart;
    if (*(temp) != 'v')   return 0; temp++;
    if (*(temp++) != 'o') return 0;
    if (*(temp++) != 'i') return 0;
    if (*(temp++) != 'd') return 0;
    return 1;
}

int NFAs::getInt() {
    temp = wordStart;
    if (*(temp) != 'i')   return 0; temp++;
    if (*(temp++) != 'n') return 0;
    if (*(temp++) != 't') return 0;
    return 1;
}

int NFAs::getReturn() {
    temp = wordStart;
    if (*(temp) != 'r')   return 0; temp++;
    if (*(temp++) != 'e') return 0;
    if (*(temp++) != 't') return 0;
    if (*(temp++) != 'u') return 0;
    if (*(temp++) != 'r') return 0;
    if (*(temp++) != 'n') return 0;
    while (*(temp++) != ';') ;
    return 1;
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
    if (*(temp++) != '(') return 0;
    return 1;
}
