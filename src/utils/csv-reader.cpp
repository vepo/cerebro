#include "utils/csv-reader.hpp"
#include "utils/debug.hpp"
#include "utils/string-utils.hpp"

std::regex CSVReader::lineRegex("^.*\\r*[$\\n]?");
std::regex CSVReader::cellRegex("^([^,\\n]*)\\r*([$,\\n]?)");
std::regex CSVReader::lineEscapedRegex("^\\s*\"(?:\"{2}|.|\n|\r)*\".*[$\\n]?");
std::regex CSVReader::cellEscapedRegex("^\\s*\"((?:\"{2}|.|\n|\r)*)\"([,$\\n]?)");

CSVReader::CSVReader(std::string path)
{
    this->input = new std::ifstream(path, std::ios::in);
    this->match = new std::smatch();
}

CSVReader::~CSVReader()
{
    delete this->input;
    delete this->match;
}

std::string CSVReader::process_line(std::smatch lineMatch)
{
    std::smatch cellMatch;
    std::string line = lineMatch.str();
    if (std::regex_search(line, cellMatch, cellEscapedRegex))
    {
        std::string cell = StringUtils::trim(StringUtils::replaceAll(cellMatch[1].str(), "\"\"", "\""));
        this->buffer.erase(0, cellMatch.length());
        this->eol = cellMatch[2] != ",";
        return cell;
    }
    else if (std::regex_search(line, cellMatch, cellRegex))
    {
        std::string cell = cellMatch[1].str();
        this->buffer.erase(0, cellMatch.length());
        this->eol = cellMatch[2] != ",";
        return StringUtils::trim(cell);
    }
    return "";
}

std::string CSVReader::nextToken()
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

    std::smatch lineMatch;
    if (std::regex_search(this->buffer, lineMatch, lineEscapedRegex))
    {
        return process_line(lineMatch);
    }
    else if (std::regex_search(this->buffer, lineMatch, lineRegex))
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
    return (!this->buffer.empty() && std::regex_search(this->buffer, cellRegex)) ||
           (this->input->is_open() && this->input->peek() != EOF);
}