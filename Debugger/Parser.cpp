#include "../Headers/All.h"

#include <cstring>
#include <unordered_set>

const char * SEMICOL         = ";";
const char * LPAREN          = "(";
const char * RPAREN          = ")";

#define  equals(t, tokens, n) ({\
    bool retVal;                \
    for (;n >= 0; n--)          \
        if (tokens[n] == t) {   \
          retVal = true;        \
          retVal;               \
        }                       \
    retVal = false;             \
    retval;\
})

bool Parser::parse() {
    if (!parsePreProc())
        return 0;
    else if (!parseProto())
        return 0;
    else if (!parseScope())
        return 0;
    return 1;
}

//Gets a the new func string and creates func itm and stores it
bool Parser::parseScope() {

    //func->retType scopeName(args){ funcBody }

    if (checkAndConsume(RETINT) || checkAndConsume(RETVOID)) {
        std::string_view scopeName = scanner->getCurrStr();
        Scope * s = new Scope(scopeName);
        consume(); consume();
        if (checkAndConsume(SCOPE))
            enterScope(s);
        else return false;
        if (!parseFuncBody()) {
            //Could Be No Func Calls in this Scope
            return false;
        }
        consume();
        exitScope();
        return true;
    }
    return false;
}

bool Parser::parseFuncBody() {
    //funcbody -> funCall funcBody
    if (check(FUNC)) {
        while(parseFuncCall())
            ;
    }
    else {
        return 0;
    }
    return 1;
}

bool Parser::parseFuncCall() {
    //funcCall -> funcName ( args );
    if (!check(FUNC))
        return 0;
    if(!scope)
        //TODO Throw ERR
        return 0;
    std::string_view FuncName = scanner->getCurrStr();
    if(!(scope->contains(FuncName))) {
        Func * f = allFuncs.at(FuncName);
        f->setNCalls();
        scope->addFunc(std::pair<std::string_view, Func *>(f->getName(), f));
    }
    consume();
    return 1;
}

bool Parser::parsePreProc() {
    //preproc -> # preprocprime word;
    if (check(PREPROC)) {
        consumeLine();
        return true;
    }
    return false;
}

bool Parser::parseProto() {

    if (check(FUNC)) {
        std::string_view FuncName = scanner->getCurrStr();
        Func * f = new Func(FuncName);
        std::pair<std::string_view, Func *> pair(f->getName(), f);
        allFuncs.insert(pair);
        parseArgs(f);
        consume();
    }
    return false;
}

bool Parser::parseArgs(Func * f) {
    if (check(ARGS)) {
        f->setArgs(&scanner->file[scanner->wf_idx], scanner->getCurrStrSize());
        return true;
    }
    return false;
}

bool Parser::checkAndConsume(int token) {
    if (Token == token) {
        scanner->readWord();
        return true;
    }
    return false;
}

bool Parser::check(int token) {
    return (Token == token);
}

void Parser::consume() {
    scanner->readWord();
}
void Parser::consumeLine() {
    scanner->readLine();
}