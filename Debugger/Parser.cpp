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
//============================================================

bool Parser::parse() {
    return parsePreProc();
    /*
    if (!parsePreProc())
        return 0;
    else if (!parseProto())
        return 0;
    else if (!parseScope())
        return 0;
    return 1;
     */
}

//TODO::Get rid of this one
bool Parser::parseScope() {

    //func->retType scopeName(args){ funcBody }
    int retType;
    if ((retType = checkAndConsume(RETINT)) || (retType = checkAndConsume(RETVOID))) {
        //TODO::Set Scope's retType using retType
        Scope *s = new Scope(scanner->getCurrStr());
        consume();
        parseArgs(s);
        consume();
        enterScope(s);
        consume();
        if (!parseFuncBody()) {
            //Could Be No Func Calls in this Scope
        }
        consume();
        exitScope();
        return true;
    }
    return false;
}

//Just need to check if scope, if true, then consume and call func bod

bool Parser::parseFunc() {
    if (checkAndConsume(RETVOID) || checkAndConsume(RETINT)) {
        if (check(FUNC)) {
            std::string_view name = scanner->getCurrStr();
            Func * f;
            if (allScopes.find(name) != allScopes.end()) {
                f = new Func(name);
                allFuncs.insert( {name, f} );
            }
            else {
                f = allFuncs[name];
            }
            consume(); parseArgs(f); consume();
            if (check(SCOPE)) {
                //TODO::Write a func to scope method
            }
            return true;
        }
    }
    return false;
}

//Just need to call consume() if true

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

//TODO::Get rid of this one
bool Parser::parseProto() {
    if (check(RETVOID) || check(RETINT))
        consume();
    if (check(FUNC)) {
        std::string_view FuncName = scanner->getCurrStr();
        Func * f = new Func(FuncName);
        std::pair<std::string_view, Func *> pair(f->getName(), f);
        allFuncs.insert(pair);
        scanner->readLine();
        return true;
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

bool Parser::parseArgs(Scope * s) {
    if (check(ARGS)) {
        s->setArgs(&scanner->file[scanner->wf_idx], scanner->getCurrStrSize());
        return true;
    }
    return false;
}