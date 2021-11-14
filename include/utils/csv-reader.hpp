#pragma once

#include <string>
#include <fstream>
#include <regex>

using namespace std;

class CSVReader
{
public:
    CSVReader(string path);
    ~CSVReader();
    string nextToken();
    bool hasNextToken();
    bool endOfLine();

    static regex lineRegex;
    static regex cellRegex;
    static regex lineEscapedRegex;
    static regex cellEscapedRegex;

private:
    string process_line(smatch lineMatch);
    bool eol;
    ifstream *input;
    smatch *match;
    string buffer;
};