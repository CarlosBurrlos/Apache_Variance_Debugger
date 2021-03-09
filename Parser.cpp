#include "Header.h"

using namespace Dbugr;

void Parser::parse() {
    //first check if there is anything to read
    if (s->peekChar() != EOF) {
        while (s->nextWord() &&
               std::regex_match(s->getCurrStr(),incOrDefRegx))
        {
            s->nextLine();
            readEmptyLines();
        }

        readEmptyLines();
        consumeProtos();
        readEmptyLines();

        while (s->peekChar() != EOF) {
            //Now we being reading our actual file
            s->clearStr();
            s->nextWord();
            //This should be handled by the parser shouldn't it?
            if (std::regex_match(s->getCurrStr(), returnTypes)){
                s->nextWord();
                std::string retType(s->getCurrStr());
                if (std::regex_match(s->getCurrStr(), mainRegx)) {
                    this->main = createMain(retType);
                    s->nextChar();
                }
                else {
                    this->enterScope(createScope(retType));
                }
                this->nScp = 1;
                s->nextChar();
                continue;
            }
            else if (std::regex_match(s->getCurrStr(), scopeProtoRegx)) {
                parseFunc(this->s->getCurrStr(), 1);
            }
            else if (std::regex_match(s->getCurrStr(), func)) {
                parseFunc(this->s->getCurrStr(), 0);
            }
            else if (std::regex_match(s->getCurrStr(), ext)) {
                this->exitScope();
            }
            else {
                //TODO Print failure message
            }
        }
    }
    printf("EOF REACHED::%d-CHARS READ\n", s->getNCharsRead());
}

void Parser::consumeProtos() {
    while (1) {
        if (s->peekChar() == '\n') break;
        //Grab "void"
        s->nextWord();
        //Grabe "scope..."
        s->nextLine();
        /*  We could parse the protos here || inside the parse loop
         if (std::regex_match(s->getCurrStr(), scopeProtoRegx)) {
            //TODO Handle the scopes with our parser
            //   >>Create their new entries
        }
        if (std::regex_match(s->getCurrStr(), funcProtoRegx)) {
            //TODO Handle the func with our parser
            //  >>Create new func instance and store
        }
        */
    }
}

void Parser::readEmptyLines() {
    while (s->peekChar() == '\n')
        s->nextLine();
}

//Gets a the new func string and creates func itm and stores it
void Parser::parseFunc(std::string funcN, int t) {
    if (t) {
        if (this->main->contains(s->getCurrStr())) {
            return;
        }
        Func *func = new Func(s->getCurrStr());
        std::pair<std::string, Func *> pair(func->getFunc(), func);
        this->main->addFunc(pair);
    }
    else {
        if (this->scp->contains(s->getCurrStr())) {
            return;
        }
        Func *func = new Func(s->getCurrStr());
        std::pair<std::string, Func *> pair(func->getFunc(), func);
        this->scp->addFunc(pair);
    }
}

void Parser::enterScope(Scope * scope) {
    this->scp = scope;
}

void Parser::exitScope() {
    if (this->scp) {
        Scopes.push_back(this->scp);
        this->scp = nullptr;
    }
}