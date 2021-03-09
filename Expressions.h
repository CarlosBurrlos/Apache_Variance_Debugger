#include<ostream>
#include<regex>

std::regex  incOrDefRegx        ("(#include|#define)");
std::regex  returnTypes         ("void|int|char|int(\\[\\])+|char(\\[\\])|bool");
std::regex  scopeProtoRegx      ("scope[0-9]+();");
std::regex  funcProtoRegx       ("\\w+\\(\\);");
std::regex  mainRegx            ("int main()");
std::regex  ret                 ("return");
std::regex  func                ("\\w+\\(\\);");
std::regex  ext                 ("}");
std::regex  printfRegx          ("printf\\(\\w+\\);");

