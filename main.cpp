#include    <iostream>
#include    "Scanner.cpp"
#include    "Parser.cpp"

using namespace Dbugr;

static constexpr auto pattern = ctll::fixed_string{ "h.*" };

constexpr auto match(std::string_view sv) noexcept {
    return ctre::match<"h.*">(sv);
}

int main() {

    Scanner * s = new Scanner("../tmp.txt");

    s->readWord();
    size_t len = s->getCurrStrSize();
    std::string_view sub(s->getWordStart(), len);

    return 0;
}