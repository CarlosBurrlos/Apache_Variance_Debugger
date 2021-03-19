//
// Created by Carlos on 3/18/21.
//

#define BAD     0
#define PREPROC 1
#define FUNC    2
#define SCOPE   3
#define RETVOID 4
#define RETINT  5
#define RETRN   6

#define a_z(c) ({\
    bool ret;               \
    ( c >= 65 || c <= 90||  \
      c >= 97 || c <= 122)  \
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

class NFAs {
    public:

        NFAs(): wordStart(nullptr){}
        ~NFAs() {if (wordStart) wordStart = nullptr;}

        int compute() {
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

        int getPreProc() {
            if (*(wordStart) != '#')  return -1;
            wordStart++;
            while (a_z(*(wordStart++))) ;
            if (*wordStart != ' ') {
                return -1;
            }
            //Read rest of line automatically
            return 1;
        }

        int getFunc() {
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

        int getScope() {
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

        int getVoid() {
            if (*(wordStart) != 'v')   return -1; wordStart++;
            if (*(wordStart++) != 'o') return -1;
            if (*(wordStart++) != 'i') return -1;
            if (*(wordStart++) != 'd') return -1;
            return 1;
        }

        int getInt() {
            if (*(wordStart) != 'i')   return -1; wordStart++;
            if (*(wordStart++) != 'n') return -1;
            if (*(wordStart++) != 't') return -1;
            return 1;
        }

        int getReturn() {
            if (*(wordStart) != 'r')   return -1; wordStart++;
            if (*(wordStart++) != 'e') return -1;
            if (*(wordStart++) != 't') return -1;
            if (*(wordStart++) != 'u') return -1;
            if (*(wordStart++) != 'r') return -1;
            if (*(wordStart++) != 'n') return -1;
            while (*(wordStart++) != ';') ;
            return 1;
        }
        void setWordStart(char * ptr) {wordStart = ptr;}
    private:
        char * wordStart;
};
