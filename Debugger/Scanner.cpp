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

//============================================================
/* Macro to check if we are at the end of the current word  */
//============================================================
#define isEndWord(ptr) ({    \
    bool ret;                \
    (*(ptr) == ' ' || *(ptr) == '(' || \
     *(ptr) == ';' || *(ptr) == '{' || \
     *(ptr) == '\n')\
        ? ret = 1 : ret = 0; \
    ret;                     \
 })
//============================================================
/* Macro to check if we are at the end of the file          */
//============================================================
#define atEOF(fIdx, fEnd) ({ \
    bool ret = false;        \
    if(fIdx == fEnd)         \
        ret = true;          \
    ret;                     \
})

//============================================================
/* Flip a checked value                                     */
//============================================================
#define set(nuWord) (nuWord = !nuWord)

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
    //============================================================
    /* Read all upcoming chars within curr word                 */
    while (true) {
        check = readChar();
        if (check == END || check == ENDWORD) 
            break;
    }
    word = getCurrStr();
//================================================================  [DB]
    //std::cout << word << '\t' << '\n';
//================================================================  [DB]
    nfa->setWordStart(&file[wf_idx], &file[we_idx]);
    Token = nfa->compute();
//================================================================
/* We will just handle reading the rest of line here
        Token :: PREPROC -> readline
                 RETRN   -> readline
*/
//================================================================
    if (Token == PREPROC || Token == RETRN) {
        readLine();
    }
//================================================================  [DB]
    //std::cout << word << '\t' << '\t' << '\t' << "TOKEN :: \t" << Token << '\n';
//================================================================  [DB]
    if (check == END)   return END;
    return OK;
}

int Scanner::readChar() {
    //============================================================
    /* IF at end of file, set end of word idx and return END    */
    if (atEOF(fIdx, eofIdx)) {
        we_idx = fIdx-1;
        set(atEnd);
        return END;
    }
    //============================================================
    /* Just a check if at start of our buff                     */
    if (fIdx == 0)
        set(nuWord);
    //============================================================
    /* Pointer at start of new word and set nuWord flag to F    */
    if (nuWord /* && fIdx - 1 >= 0*/) {
        wf_idx = fIdx++;
        set(nuWord);
        return STARTWORD;
    }
    //============================================================
    /* Pointer is at end of current word, see macros above      */
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
    //============================================================
    /* Just at normal char within current word being read       */
    else {
        fIdx++;
        return OK;
    }
    //============================================================
}

int Scanner::getCurrStrSize() const {
    //============================================================
    /* We have a problem here idxs values don't preserve order  */
    if (we_idx < wf_idx) return 0;
    //TODO::This is an error
    return (we_idx - wf_idx) + 1;
    //============================================================
}

int Scanner::readLine() {
    //============================================================
    /* Just reads the rest of the line                          */
    while (1) {
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
    //============================================================
}