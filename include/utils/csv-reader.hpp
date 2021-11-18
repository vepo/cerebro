#pragma once

#include <string>
#include <fstream>
#include <regex>

class CSVReader
{
public:
    explicit CSVReader(std::string path);
    std::string nextToken();
    bool hasNextToken();
    bool endOfLine();

    static std::regex lineRegex;
    static std::regex cellRegex;
    static std::regex lineEscapedRegex;
    static std::regex cellEscapedRegex;

private:
    std::string process_line(std::smatch lineMatch);
    bool _eol;
    std::ifstream _input;
    std::smatch _match;
    std::string _buffer;
};