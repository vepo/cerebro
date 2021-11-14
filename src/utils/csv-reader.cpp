#include "utils/csv-reader.hpp"
#include "utils/debug.hpp"
#include "utils/string-utils.hpp"

regex CSVReader::lineRegex("^.*\\r*[$\\n]?");
regex CSVReader::cellRegex("^([^,\\n]*)\\r*([$,\\n]?)");
regex CSVReader::lineEscapedRegex("^\\s*\"(?:\"{2}|.|\n|\r)*\".*[$\\n]?");
regex CSVReader::cellEscapedRegex("^\\s*\"((?:\"{2}|.|\n|\r)*)\"([,$\\n]?)");

CSVReader::CSVReader(string path)
{
    this->input = new ifstream(path, ios::in);
    this->match = new smatch();
}

CSVReader::~CSVReader()
{
    delete this->input;
    delete this->match;
}

string CSVReader::process_line(smatch lineMatch)
{
    smatch cellMatch;
    string line = lineMatch.str();
    if (regex_search(line, cellMatch, cellEscapedRegex))
    {
        string cell = StringUtils::trim(StringUtils::replaceAll(cellMatch[1].str(), "\"\"", "\""));
        this->buffer.erase(0, cellMatch.length());
        this->eol = cellMatch[2] != ",";
        return cell;
    }
    else if (regex_search(line, cellMatch, cellRegex))
    {
        string cell = cellMatch[1].str();
        this->buffer.erase(0, cellMatch.length());
        this->eol = cellMatch[2] != ",";
        return StringUtils::trim(cell);
    }
    return "";
}

string CSVReader::nextToken()
{
    if (this->input->is_open())
    {
        if (this->buffer.empty())
        {
            char readBuffer[1024] = {};
            if (this->input->readsome(readBuffer, 1024) > 0)
            {
                this->buffer.append(readBuffer);
            }
        }
    }

    smatch lineMatch;
    if (regex_search(this->buffer, lineMatch, lineEscapedRegex))
    {
        return process_line(lineMatch);
    }
    else if (regex_search(this->buffer, lineMatch, lineRegex))
    {
        return process_line(lineMatch);
    }
    return "";
}

bool CSVReader::endOfLine()
{
    return this->eol;
}

bool CSVReader::hasNextToken()
{
    return (!this->buffer.empty() && regex_search(this->buffer, cellRegex)) ||
           (this->input->is_open() && this->input->peek() != EOF);
}