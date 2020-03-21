#include <dbg/utils.h>

#include <sstream>

std::vector<std::string> split(const std::string& str, char delimeter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream iss(str);

    while (std::getline(iss, token, delimeter)) {
        tokens.push_back(token);
    }

    return tokens;
}

bool is_prefix(const std::string& str, const std::string& of) {
    if (str.size() > of.size()) return false;
    return std::equal(str.begin(), str.end(), of.begin());
}
