#include    "../Headers/All.h"

#include    <cassert>
#include    <fcntl.h>
#include    <sys/stat.h>
#include    <sys/mman.h>
#include    <unistd.h>
#include    <iostream>

int Token = 0;

std::unordered_map<std::string_view/*scpName*/, Scope *> allScopes;
std::unordered_map<std::string_view/*Name*/,Func *> allFuncs;

#define isEndWord(ptr) ({    \
    bool ret;                \
    (*(ptr) == ' ' || *(ptr) == '(' || \
     *(ptr) == ';' || *(ptr) == '{' || \
     *(ptr) == '\n')\
        ? ret = 1 : ret = 0; \
    ret;                     \
 })

#define atEOF(fIdx, fEnd) ({ \
    bool ret = false;        \
    if(fIdx == fEnd)         \
        ret = true;          \
    ret;                     \
})

#define set(nuWord) (nuWord = !nuWord)

#define BADWORD     -4
#define ENDWORD     -2
#define ERR         -1
#define NOTEQUAL    -1
#define OK           1
#define EQUAL        1
#define STARTWORD    2
#define END          3

[[maybe_unused]] char debuggingChar;

Scanner::Scanner(const char * fName)
: wf_idx(0), we_idx(0), fIdx(0), nuWord(false),
  atEnd(false),  nfa(nullptr)
{
    fileDescpt = open(fName, O_RDONLY);
    assert(fileDescpt != -1);
	struct stat sb{}; fstat(fileDescpt, &sb);
	eofIdx = sb.st_size;
	file = (char *)
	        mmap(nullptr, sb.st_size,PROT_READ,MAP_PRIVATE, fileDescpt, 0);
	assert(file);
    nfa = new NFAs();
}

Scanner::~Scanner() {
	close(fileDescpt);
	fileDescpt = -1;
	munmap(file, eofIdx); //May have to decrememnt by 1
	file = nullptr;
}

int Scanner::readWord () {
    int check;
    while (true) {
        check = readChar();
        if (check == END || check == ENDWORD) 
            break;
    }
    word = std::string_view (&file[wf_idx], getCurrStrSize());

    std::cout << word << '\n';
    nfa->setWordStart(&file[wf_idx], &file[we_idx]);
    Token = nfa->compute();
    if (check == END)   return END;
    return OK;
}

int Scanner::readChar() {
    if (atEOF(fIdx, eofIdx)) {
        we_idx = fIdx-1;
        set(atEnd);
        return END;
    }
    if (fIdx == 0)
        set(nuWord);
    //We are at new word
    if (nuWord /* && fIdx - 1 >= 0*/) {
        wf_idx = fIdx++;
        set(nuWord);
        return STARTWORD;
    }
    //Reached end of word
    else if (isEndWord(&file[fIdx])) {
        if (file[fIdx] == ' ' || file[fIdx] == '\n')
            we_idx = fIdx - 1;
        else 
            we_idx = fIdx;
        fIdx++;
        if (file[fIdx] == '\n')
            while(file[fIdx] == '\n' && fIdx != eofIdx) {fIdx++;}
        while(file[fIdx] == ' ' && fIdx != eofIdx) {fIdx++;}
        if (fIdx == eofIdx)
            return END;
        set(nuWord);
        return ENDWORD;
    }
    //Just read next char
    else {
        fIdx++;
        return OK;
    }
}

int Scanner::getCurrStrSize() const {
    if (we_idx < wf_idx) return 0;
    return (we_idx - wf_idx) + 1;
}

int Scanner::readLine() {
    while (1) {
        if (file[fIdx] != '\n'){
            break;
        }
        if (fIdx == eofIdx) {
            we_idx = fIdx - 1;
            set(atEnd);
            return END;
        }
        fIdx++;
    }
    fIdx++;
    set(nuWord);
    return OK;
}