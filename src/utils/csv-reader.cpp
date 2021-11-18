#include "utils/csv-reader.hpp"
#include "utils/debug.hpp"
#include "utils/string-utils.hpp"

std::regex CSVReader::lineRegex("^.*\\r*[$\\n]?");
std::regex CSVReader::cellRegex("^([^,\\n]*)\\r*([$,\\n]?)");
std::regex CSVReader::lineEscapedRegex("^\\s*\"(?:\"{2}|.|\n|\r)*\".*[$\\n]?");
std::regex CSVReader::cellEscapedRegex("^\\s*\"((?:\"{2}|.|\n|\r)*)\"([,$\\n]?)");

CSVReader::CSVReader(std::string path) : _input(path, std::ios::in)
{
}

std::string CSVReader::process_line(std::smatch lineMatch)
{
    std::smatch cellMatch;
    std::string line = lineMatch.str();
    if (std::regex_search(line, cellMatch, cellEscapedRegex))
    {
        std::string cell = StringUtils::trim(StringUtils::replaceAll(cellMatch[1].str(), "\"\"", "\""));
        _buffer.erase(0, cellMatch.length());
        _eol = cellMatch[2] != ",";
        return cell;
    }
    else if (std::regex_search(line, cellMatch, cellRegex))
    {
        std::string cell = cellMatch[1].str();
        _buffer.erase(0, cellMatch.length());
        _eol = cellMatch[2] != ",";
        return StringUtils::trim(cell);
    }
    return "";
}

std::string CSVReader::nextToken()
{
    if (_input.is_open())
    {
        if (_buffer.empty())
        {
            char readBuffer[1024] = {};
            if (_input.readsome(readBuffer, 1024) > 0)
            {
                _buffer.append(readBuffer);
            }
        }
    }

    std::smatch lineMatch;
    if (std::regex_search(_buffer, lineMatch, lineEscapedRegex))
    {
        return process_line(lineMatch);
    }
    else if (std::regex_search(_buffer, lineMatch, lineRegex))
    {
        return process_line(lineMatch);
    }
    return "";
}

bool CSVReader::endOfLine()
{
    return _eol;
}

bool CSVReader::hasNextToken()
{
    return (!_buffer.empty() && std::regex_search(_buffer, cellRegex)) ||
           (_input.is_open() && _input.peek() != EOF);
}