#pragma once

#include <string>
#include <fstream>
#include <regex>

class CSVReader
{
public:
    CSVReader(std::string path);
    ~CSVReader();
    std::string nextToken();
    bool hasNextToken();
    bool endOfLine();

    static std::regex lineRegex;
    static std::regex cellRegex;
    static std::regex lineEscapedRegex;
    static std::regex cellEscapedRegex;

private:
    std::string process_line(std::smatch lineMatch);
    bool eol;
    std::ifstream *input;
    std::smatch *match;
    std::string buffer;
};