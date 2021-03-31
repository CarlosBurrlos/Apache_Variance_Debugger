#include "../Headers/All.h"

#include <unordered_set>

//========================= Helpers ==========================
bool Parser::checkAndConsume(int token) {
    if (Token == token) { scanner->readWord(); return true; }
    else return false;
}
bool Parser::check(int token) {return (Token == token);}
void Parser::consume() {scanner->readWord();}
void Parser::consumeLine() {scanner->readLine();}
bool Parser::atEnd() {
    if (scanner->fIdx == scanner->eofIdx)   scanner->atEnd = true;
    return scanner->atEnd;
}
//============================================================

bool Parser::parse() {
    while (parsePreProc())
        ;
    while (parseFunc())
        if (check(SCOPE))
            goto label;
        ;

    while (parseFunc()) {
        label:
        if (checkAndConsume(SCOPE)) {
            if (checkAndConsume(RETRN)) {
                checkAndConsume(EXT_SCOPE);
                scope = nullptr;
                continue;
            }

            //Consume all funcCalls inside the scope body
            if (parseFuncBody()){
                checkAndConsume(RETRN);
            }

            //When we reach the end of the scope, reset scope ptr
            if (checkAndConsume(EXT_SCOPE)) {
                scope = nullptr;
            }
            //TODO::If-Else throws error if any hiccups
            ;
        }
        ;
    }
    if (!atEnd())   return false; //TODO::Throw error
    return true;
}

bool Parser::parseFunc() {
    if (checkAndConsume(RETVOID) || checkAndConsume(RETINT)) {
        if (check(FUNC)) {
            std::string_view name = scanner->getCurrStr();
            Func * f = nullptr; Scope * s = nullptr;
            //To avoid all this overhead, we could use inheritnc.

            if (allFuncs.find(name) == allFuncs.end()) {
                f = new Func(name);
                allFuncs.insert( {name, f} );
            }
            else {
                f = allFuncs[name];
            }
            consume();
            parseArgs(f);
            consume();
            if (check(SCOPE)) {
                if (!(s = f->convertToScope()))
                    ;
                scope = s;
            }
            return true;
        }
    }
    return false;
}

bool Parser::parseFuncBody() {
    //funcbody -> funCall funcBody
    while(parseFuncCall())
        ;
    return 1;
}

//TODO::Test more - Good so far
bool Parser::parseFuncCall() {
    //funcCall -> funcName ( args );
    if (!check(FUNC))
        return false;
    if(!scope)
        return 0; //TODO Throw ERR
    std::string_view FuncName = scanner->getCurrStr();
    if(!(scope->contains(FuncName))) {
        Func * f = allFuncs.at(FuncName);
        f->setNCalls();
        scope->addFunc( {FuncName, f} );
    }
    consume();consume(); //We dont need the args
    return true;
}

//TODO::Test more - Good so far

//Note: Do not need to read the rest of line
//  > This is handled inside the token computation

bool Parser::parsePreProc() {
    //preproc -> # preprocprime word;
    consume();
    if (check(PREPROC)) {
        return true;
    }
    return false;
}

bool Parser::parseArgs(Func * f) {
    if (check(ARGS)) {
        f->setArgs(&scanner->file[scanner->wf_idx],
                   scanner->getCurrStrSize());
        return true;
    }
    return false;
}
