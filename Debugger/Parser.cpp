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

void Parser::parse() {

   //parse -> preProcs protos parseFuncs
                //parseFuncCalls parseReturn

}

//Gets a the new func string and creates func itm and stores it
bool Parser::parseScope() {

    //func->retType scopeName(args){ funcBody }

    if (Token == RETINT || Token == RETVOID) {
        consume();
        std::string_view scopeName = scanner->getCurrStr();
        Scope * s = new Scope(scopeName);
        consume();  //TODO Parse Args
        enterScope(s);
        consume();

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

void Parser::enterScope(Scope * s) {
    scope = s;
}

void Parser::exitScope() {

    if (scope) {
        std::pair<std::string_view, Scope *> pair(scope->getScope(), scope);
        allScopes.insert(pair);
        this->scope = nullptr;
    }
}

bool Parser::parsePreProc() {
    //preproc -> # preprocprime word;
    if (Token == PREPROC) {
        consumeLine();
        return true;
    }
    return false;
}

bool Parser::parseProto() {

    if (Token == FUNC) {
        std::string_view FuncName = scanner->getCurrStr();
        Func * f = new Func(FuncName);
        std::pair<std::string_view, Func *> pair(f->getName(), f);
        allFuncs.insert(pair);
        parseArgs(f);
        consume();
    }
    return false;
}

bool Parser::parseFuncBody() {
    //funcbody -> funCall funcBody
    if (Token == FUNC) {
        parseFuncCall();
        parseFuncBody();
    }
    else {
        return 0;
    }
    return 1;
}

bool Parser::parseFuncCall() {
    //funcCall -> funcName ( args );
    if(!scope)
        //TODO Throw ERR
        return 0;
    std::string_view FuncName = scanner->getCurrStr();
    if(!scope->contains(FuncName)) {
        Func * f = allFuncs.at(FuncName);
        f->setNCalls();
        scope->addFunc(std::pair<std::string_view, Func *>(f->getName(), f));
    }
    consume();
    return 1;
}

bool Parser::parseArgs(Func * f) {
    //scanner->readTill(*RPAREN);
    //f->setArgs(scanner->getWordStart(), scanner->getCurrStrSize());
    return true;
}

void Parser::consume() {
    scanner->readWord();
}
void Parser::consumeLine() {
    scanner->readLine();
}