#include "utils/string-utils.hpp"
#include <regex>

std::string StringUtils::trim(std::string value)
{
    return std::regex_replace(std::regex_replace(value, std::regex("^\\s*"), ""), std::regex("\\s*$"), "");
}

std::string StringUtils::replaceAll(std::string original, std::string pattern, std::string replacement)
{
    std::string dest = original;
    size_t pos;
    while ((pos = dest.find(pattern)) != std::string::npos)
    {
        dest.replace(pos, pattern.length(), replacement);
    }
    return dest;
}