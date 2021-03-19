#include <cstring>
#include <unordered_set>
using namespace Dbugr;

void Parser::parse() {
   //parse -> preProcs protos parseFuncs
                //parseFuncCalls parseReturn

    //Parse the preproc items
   //First parse prototype items
    parsePreProc();
    while (!(scanner->nuWord))  parseProto();    //Parse all of our funcs
    while (!(scanner->atEnd)) parseFunc();
}

//Gets a the new func string and creates func itm and stores it
void Parser::parseFunc() {
    //func->retType funcName ( args ) { funcBody }
    if (getToken() == RETINT || getToken() == RETVOID) {
        consume();  //Will have to change our NFA to accept this funcbody
        //Implement how ot get our scope name
        Scope * s = new Scope("\\");
        enterScope(s);
        parseFuncBody();
        exitScope();
        consume();
    }
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

bool Parser::checkAndConsume(std::regex r) {
    return 0;
}

bool Parser::check(std::regex r) {
    return 0;
}

//need to get next char first
void Parser::parsePreProc() {
    //preproc -> # preprocprime word;
    if (getToken() == PREPROC) {
        consumeLine();
    }

}

void Parser::parseProto() {

}

bool Parser::parseFuncBody() {
    //funcbody -> funCall funcBody
    if (getToken() == FUNC) {
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
    char *func = nullptr;
    this->scanner->readTill('('); this->scanner->fIdx--;
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
        args.insert(arg);
    }
    return args;
}

int Parser::consume() {
    if(scanner->readWord() == ERR)      return ERR;
    else                                return OK;
}

void Parser::consumeLine() {
    scanner->readLine();
}