#pragma once

#include <string>
#include <regex>

using namespace std;
class StringUtils
{
public:
    static string trim(string value);
    static string replaceAll(string value, string pattern, string replacement);
};
