#include<ostream>
#include<regex>

std::regex  incOrDefRegx        ("(#include|#define)");
std::regex  returnTypes         (R"(void|int|char|int(\[\])+|char(\[\])|bool)");
std::regex  scopeProtoRegx      ("scope[0-9]+();");
std::regex  funcProtoRegx       (R"(\w+\(\);)");
std::regex  mainRegx            ("int main()");
std::regex  ret                 ("return");
std::regex  func                (R"(\w+\(\);)");
std::regex  ext                 ("}");
std::regex  printfRegx          (R"(printf\(\w+\);)");

