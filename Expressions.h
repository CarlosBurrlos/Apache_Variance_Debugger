#include<ostream>
#include<regex>

std::string entrScp     = "[\\w]+ [\\w]+\\(.*\\)\\{";
std::string extScp      = "}";
std::string funcCall    = "[\\w]{1,}\\(.*\\);";
std::string ret         = "return";
std::string word        = "[\\w]+";
std::string params      = "\\(" + word + "\\)";

std::regex  eScp(entrScp);
std::regex  exScp(extScp);
std::regex  fCall(funcCall);
std::regex  wrd(word);
std::regex  rt(ret);
std::regex  prms(params);

std::regex regs [] = {eScp, exScp, fCall, wrd, rt, prms};

