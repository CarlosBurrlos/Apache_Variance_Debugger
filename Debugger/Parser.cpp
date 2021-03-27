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
bool Parser::atEnd() {return scanner->atEnd;}
//============================================================

bool Parser::parse() {
    while (parsePreProc())
        ;
    while (parseFunc())
        if (checkAndConsume(SCOPE) &&
           (checkAndConsume(RETVOID) || checkAndConsume(RETINT)))
            if(parseFuncBody())
                if (!checkAndConsume(RETRN))
                   return false;
            if (check(EXT_SCOPE))
                scope = nullptr;
            else
                ;//TODO::Throw error
        ;;
    if (!atEnd())   return false; //TODO::Throw error
    return true;
}

bool Parser::parseFunc() {
    if (checkAndConsume(RETVOID) || checkAndConsume(RETINT)) {
        if (check(FUNC)) {
            std::string_view name = scanner->getCurrStr();
            Func * f; Scope * s;
            if (allScopes.find(name) != allScopes.end()) {
                f = new Func(name);
                allFuncs.insert( {name, f} );
            }
            else {
                f = allFuncs[name];
            }
            consume(); parseArgs(f); consume();
            if (check(SCOPE)) {
                if (!(s = f->convertToScope())) {
                    //TODO::Throw Error
                }
                scope = s;
            }
            return true;
        }
    }
    return false;
}

bool Parser::parseFuncBody() {
    //funcbody -> funCall funcBody
    if (check(FUNC)) {
        while(parseFuncCall())
            ;
        return 1;
    }
    return 0;
}

//TODO::Test more - Good so far
bool Parser::parseFuncCall() {
    //funcCall -> funcName ( args );
    if(!scope)
        return 0; //TODO Throw ERR
    std::string_view FuncName = scanner->getCurrStr();
    if(!(scope->contains(FuncName))) {
        Func * f = allFuncs.at(FuncName);
        f->setNCalls();
        scope->addFunc( {FuncName, f} );
    }
    consume(); //We dont need the args
    return true;
}

//TODO::Test more - Good so far
bool Parser::parsePreProc() {
    //preproc -> # preprocprime word;
    if (check(PREPROC)) {
        consumeLine();
        parsePreProc();
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
