#include "utils/string-utils.hpp"
#include <regex>

string StringUtils::trim(string value)
{
    return regex_replace(regex_replace(value, regex("^\\s*"), ""), regex("\\s*$"), "");
}

string StringUtils::replaceAll(string original, string pattern, string replacement)
{
    string dest = original;
    size_t pos;
    while ((pos = dest.find(pattern)) != string::npos)
    {
        dest.replace(pos, pattern.length(), replacement);
    }
    return dest;
}