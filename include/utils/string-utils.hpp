#pragma once

#include <string>
#include <regex>

class StringUtils
{
public:
    static std::string trim(std::string value);
    static std::string replaceAll(std::string value, std::string pattern, std::string replacement);
};
