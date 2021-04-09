#include "../include/Scanner.h"
#include "../include/Globals.h"

#include    <iostream>
#include    <cassert>
#include    <fcntl.h>
#include    <sys/stat.h>
#include    <sys/mman.h>
#include    <unistd.h>

int Token = 0;

std::unordered_map<std::string_view/*scpName*/, scp *> allScopes;
std::unordered_map<std::string_view/*Name*/,func *> allFuncs;

/*
#define is_0_9(ptr) ({ \
bool ret;              \
(*(ptr) >= 48 && *(ptr) <= 57)\
    ? ret = 1 : ret = 0;      \
ret;\
})
*/

#define isWordStart(ptr) ({ \
bool ret;                   \
((*(ptr) == '<' && *(ptr+1) == '<')\
||(*(ptr) == '\'')\
||(*(ptr) == '#'))\
    ? ret = 1 : ret = 0;\
ret;\
})\

#define isEndWord(ptr) ({    \
    bool ret;                \
    (*(ptr) == '\'' || *(ptr) == '\n' ||\
    (*(ptr) == '>')) \
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

Scanner::Scanner(const char * fName)
: wf_idx(0), we_idx(0), fIdx(0), nuWord(true),
  atEnd(false),  nfa(nullptr)
{
    fileDescpt = open(fName, O_RDONLY);
    assert(fileDescpt != -1);
	struct stat sb = {};
    if (fstat(fileDescpt, &sb) == -1) {
        exit(0);
    }
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
    if (nuWord) {
        while (!isWordStart(&file[fIdx]))
            fIdx++;
        if (file[fIdx] == '<') fIdx+=2;
        if (file[fIdx] == '\'') fIdx++;
        if (file[fIdx] == '#') {
            while (file[fIdx] != '=') fIdx++;
            fIdx++;
        }
        wf_idx = fIdx++;
        set(nuWord);
        return STARTWORD;
    }
    else if (isEndWord(&file[fIdx])) {
        we_idx = fIdx - 1;
        fIdx++;
        if (file[fIdx] == '\n')
            while(file[fIdx] == '\n' && fIdx != eofIdx) {fIdx++;}
        while(file[fIdx] == ' ' && fIdx != eofIdx) {fIdx++;}
        if (fIdx == eofIdx)
            return END;
        set(nuWord);
        return ENDWORD;
    }
    else {
        fIdx++;
        return OK;
    }
}

int Scanner::readLine() {
    while (true) {
        if (file[fIdx] == '\n'){
            while (file[fIdx] == '\n')
                fIdx++;
            break;
        }
        if (fIdx == eofIdx) {
            we_idx = fIdx - 1;
            set(atEnd);
            return END;
        }
        fIdx++;
    }
    return OK;
}

int Scanner::readTill(char c) {
    int nCharsRead = 0;
    while(file[fIdx] != c) {
        fIdx++; nCharsRead++;
    }
    return nCharsRead;
}