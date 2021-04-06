#include "../Headers/All.h"
#include <unordered_set>
#include <iostream>
//========================= Helpers ==========================
bool Parser::checkAndConsume(int token) {
    if (Token == token) { scanner->readWord(); return true; }
    else return false;
}
bool Parser::check(int token) {return (Token == token);}
void Parser::consume() {scanner->readWord();}
bool Parser::atEnd() {
    if (scanner->fIdx == scanner->eofIdx)   scanner->atEnd = true;
    return scanner->atEnd;
}
//============================================================

bool Parser::parse() {
    while (parsePreProc())
        ;
    while (parseFunc()) {
        if (check(ENTR_SCOPE)) {
            goto label;
        }
        ;
    }
    while (parseScope()) {
        label:
        if (checkAndConsume(ENTR_SCOPE)) {
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
               if (scope->name != "main(")
                   compute_support(scope);
               scope = nullptr;
            }
            //TODO::If-Else throws error if any hiccups
            ;
        }
        ;
    }
    scan_for_bugs();
    //[DB]
    /*==========================================================================================
    for (const auto & [ key, value ] : Scopes) {
        std::cout << "Scope:: " << key << '\n';
        for (const auto & [ key, value ] : value->Funcs) {
            std::cout << "    Func:: " << key << '\n';
            std::cout << "        Pairs:: " << '\n';
            for (const auto & [ key, value ] : value->pairs) {
                std::cout << "          " << "Name: "<< key  << " Count: " << value << '\n';
            }
        }
    }
    ==========================================================================================*/
    //[DB]
    return true;
}

bool Parser::parseFunc() {
    if (checkAndConsume(RETVOID) || checkAndConsume(RETINT)) {
        if (check(FUNC)) {
            std::string_view name = scanner->getCurrStr();
            if (name == "main(") {
                scp * _s = nullptr;
                if (Scopes.find(name) == Scopes.end()) {
                    _s = newScope(name);
                    Scopes.insert({name, _s});
                    scope = _s;
                }
                consume();
                consume();
                return true;
            }
            func * _f = nullptr;
            if (Functions.find(name) == Functions.end()) {
                _f = newFunc(name);
                Functions.insert({name, _f});
            }
            consume();
            consume();
        }
        else if (check(SCOPE)) {
            std::string_view name = scanner->getCurrStr();
            scp * _s = nullptr;
            if (Scopes.find(name) == Scopes.end()) {
                _s = newScope(name);
                Scopes.insert({name, _s});
            }
            consume();
            consume();
        }
        return true;
    }
    return false;
}

bool Parser::parseScope() {
    if (check(RETVOID) || check(RETINT)) {
        consume();
        if (check(SCOPE)) {
            //consume args
            std::string_view scp_name = scanner->getCurrStr();
            consume();
            consume();
            if (check(ENTR_SCOPE)) {
                scope = Scopes.find(scp_name)->second;
                return true;
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
    if (!check(FUNC) && !check(SCOPE)) {
        return false;
    }
    if(!scope) {
        return 0; //TODO Throw ERR
    }
    //We do not need to expand our scopes - request of worksheet
    if (check(SCOPE)) {
        consume(); consume();
        return true;
    }
    std::string_view FuncName = scanner->getCurrStr();
    if(!find(scope, FuncName)) {
        func * f = Functions.at(FuncName);
        f->nCalls++;
        addFunc(scope, f);
    }
    consume();consume(); //We dont need the args
    return true;
}

bool Parser::parsePreProc() {
    //preproc -> # preprocprime word;
    consume();
    if (check(PREPROC)) {
        return true;
    }
    return false;
}