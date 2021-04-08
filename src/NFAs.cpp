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
    if (getScope())
        return SCOPE;
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