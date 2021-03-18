#include "Debugger.h"
#include <regex>

#define isEndWord(ptr) ({    \
    bool ret;                \
    (*(ptr) == ' ' || *(ptr) == '\n' || *(ptr) == '\t')\
        ? ret = 1 : ret = 0; \
    ret;                     \
 })

#define atEOF(fIdx, fEnd) ({ \
    bool ret = false;        \
    if(fIdx == fEnd)         \
        ret = true;          \
    ret;                     \
})

#define set(nuWord) (nuWord = nuWord^nuWord)

#define END         -5
#define BADWORD     -4
#define ENDWORD     -2
#define ERR         -1
#define NOTEQUAL    -1
#define NONE         0
#define OK           1
#define EQUAL        1
#define STARTWORD    2


using namespace Dbugr;

Scanner::Scanner(const char * fName)
: wf_idx(0), we_idx(0), fIdx(0),
  nuWord(true)
{
    fileDescpt = open(fName, O_RDONLY);
    assert(fileDescpt != -1);
	struct stat sb{}; fstat(fileDescpt, &sb);
	eofIdx = sb.st_size;
	file = (char *)
	        mmap(nullptr, sb.st_size,PROT_READ,MAP_PRIVATE, fileDescpt, 0);
	assert(file);
    currWord = (char **) malloc(sizeof(char *) * 2);
    currWord[0] = &file[0];
}

Scanner::~Scanner() {
	close(fileDescpt);
	fileDescpt = -1;
	free(currWord); currWord = nullptr;
	munmap(file, eofIdx); //May have to decrememnt by 1
	file = nullptr;
}

int Scanner::readWord () {
    while (true) {
        int check = readChar();

        if (check == END)               return ERR;
        else if (check == ENDWORD)      break;
        else if (check == STARTWORD)    set(nuWord);
    }
    return OK;
}

int Scanner::readChar() {
    if (atEOF(fIdx, eofIdx)) {
        return END;
    }
    //We are at new word
    if (!(nuWord) && fIdx - 2 >= 0 && fIdx - 2 == we_idx) {
        wf_idx = fIdx;
        fIdx++;
        currWord[0] = &file[wf_idx];
        return STARTWORD;
    }
    //Reached end of word
    else if (isEndWord(&file[fIdx])) {
        we_idx = fIdx-1;
        fIdx++;
        currWord[1] = &file[we_idx];
        set(nuWord);
        return ENDWORD;
    }
    //Just read next char
    else {
        fIdx++;
        return OK;
    }
}

char Scanner::getCurrChar() {
    return file[fIdx];
}

int Scanner::printCurrStr() {
    std::cout.flush();

    if (!(nuWord)) {
        int n = 0;
        do { std::cout << file[wf_idx + n]; }
        while (n++ < (we_idx - wf_idx));
        return OK;
    }
    return ERR;
}

int Scanner::currStrCmp(char * w) {
    int f = 0, e = we_idx - wf_idx, w_size = strlen(w) - 1;
    if (e != w_size) return BADWORD;
    for (; f <= e;) {
        if ((file[wf_idx + f] == w[f]) &&
            (file[wf_idx + e] == w[e])) {
            f++; e--;
        }
        else {
            return NOTEQUAL;
        }
    }
    return EQUAL;
}

int Scanner::readTill(char cc) {
    return 0;
}