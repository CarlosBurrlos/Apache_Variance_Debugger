#include <cstring>
#include <unordered_set>

using namespace Dbugr;

void Parser::parse() {
   //parse -> preProcs protos parseFuncs
                //parseFuncCalls parseReturn

    //Parse the preproc items
   //First parse prototype items



}

//Gets a the new func string and creates func itm and stores it
void Parser::parseFunc() {
    //func->retType funcName ( args ) { funcBody }
    scanner->readWord(); scanner->readChar();
    char * func;
    this->scanner->readTill('('); this->scanner->fIdx--;
    //strncpy(func, reinterpret_cast <const char *>(scanner->f[scanner->wordStrt]), scanner->getCurrStr());
    scanner->readChar();
    std::unordered_set<char *> args = parseArgs();
    //TODO add args to func item
    scanner->readLine();
    auto * scope = new Scope(func);
    enterScope(scope); parseFuncBody(); exitScope();
}

void Parser::enterScope(Scope * scope) {
    this->scope = scope;
}

void Parser::exitScope() {
    if (this->scope) {
        std::pair<std::string, Scope *> pair(scope->getScope(), scope);
        allScopes.insert(pair);
        this->scope = nullptr;
    }
}

char Parser::getCurrTokenC() {
    return this->scanner->getCurrChar();
}


bool Parser::checkAndConsume(std::regex r) {
    if (std::regex_match(this->getCurrToken(), r)) {
        this->scanner->readWord();
        return 1;
    } else return 0;
}

bool Parser::check(std::regex r) {
    return (std::regex_match(this->getCurrToken(), r));
}

//need to get next char first
void Parser::parsePreProc() {
    //preproc -> # preprocprime word;
    if (getCurrTokenC() == *POUND) {
        this->scanner->readWord();
        if (parsePreProcPrime()) {
            this->scanner->readLine();    //We dont care about the word
            return;
        }
        else {
            //TODO::Throw an ERROR
            return;
        }
    }
    else {
        //TODO::Throw an ERROR
        return;
    }
}
bool Parser::parsePreProcPrime() {
    //preProcPrime -> include | define
    if (checkAndConsume(PPROC)) return 1;
    else {
        //TODO:: Throw an ERROR
        return 0;
    }
}
void Parser::parseProto() {
    //prototype -> rettype funcname;
    if (check(PPROC)) {
       char * retType;
       strncpy(retType, reinterpret_cast<const char *>(scanner->f[scanner->wordStrt]), scanner->getCurrStr());
       this->scanner->readWord();
       char * funcN;
       strncpy(funcN, reinterpret_cast<const char *>(scanner->f[scanner->wordStrt]), scanner->getCurrStr());
       Func * func = new Func(funcN);
       //TODO::Add to global funcs
       //TODO:: Func should let retype passing
       return;
    }
    else {
        //TODO::
    }
}
bool Parser::parseFuncBody() {
    //funcbody -> funCall funcBody    
    if (parseFuncCall()) {
        if (parseFuncBody()){
            return 1;
        }
    }
    else {
        //TODO::
    }
    return 0;
}
bool Parser::parseFuncCall() {
    //funcCall -> funcName ( args );
    char *func = nullptr;
    this->scanner->readTill('('); this->scanner->fIdx--;
    strncpy(func, reinterpret_cast <const char *>(scanner->f[scanner->wordStrt]), scanner->getCurrStr());
    if (scope->hasFunc(func)) {
        //Scope->funcs.push_back(glblFuncs->get(func))//
    }
    this->scanner->readChar();
    std::unordered_set<char *> args = parseArgs();
    //TODO add args to func item
    this->scanner->readChar();
    return 1;
}
std::unordered_set<char * /*args*/> Parser::parseArgs() {
    std::unordered_set <char * /*arg*/> args;
    while(this->scanner->getCurrChar() != *RPAREN) {
        int fr, e;
        char * arg;
        this->scanner->readTill(*COM); this->scanner->fIdx--;
        e = this->scanner->fIdx; fr = e - this->scanner->getCurrChar();
        strncpy(arg, reinterpret_cast <const char *> (this->scanner->f[fr]), e - fr);
        args.insert(arg);
        this->scanner->readChar();
        this->scanner->wordStrt = scanner->fIdx;
    }
    return args;
}