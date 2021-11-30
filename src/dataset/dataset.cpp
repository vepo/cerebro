#include <limits>
#include <cmath>

#include "utils/string-utils.hpp"
#include "dataset/dataset.hpp"
#include "utils/csv-reader.hpp"
#include "utils/random.hpp"

#include <iostream>

Dataset::Dataset(std::string const &path) : _cols(0), _rows(0)
{
    CSVReader reader(path);

    int counter = 0;
    while (reader.hasNextToken())
    {
        if (!counter)
        {
            _names.emplace_back(reader.nextToken());
            _cols++;
        }
        else
        {
            if (reader.endOfLine())
            {
                _contents.emplace_back();
            }
            _contents[counter - 1].emplace_back(reader.nextToken());
        }

        if (reader.endOfLine())
        {
            counter++;
        }
    }
    _rows = counter - 1;
    for (size_t col = 0; col < _names.size(); ++col)
    {
        NormalizeRule rule = Normalizer::inferRule(rowData(col));
        if (rule.type != DataType::UNDEFINED)
        {
            this->_rules[_names[col]] = rule;
        }
    }
}

Dataset::Dataset(const std::vector<std::string> &names,
                 const std::vector<std::vector<std::string>> &contents,
                 const std::map<std::string, NormalizeRule> &rules) : _names(names),
                                                                      _contents(contents),
                                                                      _cols(names.size()),
                                                                      _rows(contents.size()),
                                                                      _rules(rules)
{
}

std::string Dataset::cell(int row, int col)
{
    return _contents[row][col];
}

int Dataset::colIndex(const std::string &colName) const
{
    auto it = std::find(_names.begin(), _names.end(), colName);
    if (it != _names.end())
    {
        return (int)(it - _names.begin());
    }
    else
    {
        return -1;
    }
}

std::string Dataset::cell(int row, const std::string &colName)
{
    int colIndex = this->colIndex(colName);
    if (colIndex >= 0)
    {
        return _contents[row][colIndex];
    }
    else
    {
        return "";
    }
}

Dataset Dataset::split(const std::vector<std::string> &columnNames) const
{
    std::vector<int> columns;
    for (const auto &columnName : columnNames)
    {
        int index = this->colIndex(columnName);
        if (index >= 0)
        {
            columns.emplace_back(index);
        }
    }
    return this->split(columns);
}

Dataset Dataset::split(const std::vector<int> &colums) const
{
    std::vector<std::string> splitedColumnNames;
    std::vector<std::vector<std::string>> splitedContents;
    auto initialize_row = [=, &splitedContents]([[maybe_unused]] auto &__)
    { splitedContents.emplace_back(); };
    std::for_each(_contents.cbegin(), _contents.cend(), initialize_row);

    std::map<std::string, NormalizeRule> rules;
    for (const auto &index : colums)
    {
        splitedColumnNames.emplace_back(_names[index]);
        for (size_t row = 0; row < _contents.size(); ++row)
        {
            splitedContents[row].emplace_back(_contents[row][index]);
        }

        if (_rules.find(_names[index]) != _rules.end())
        {
            rules[_names[index]] = _rules.at(_names[index]);
        }
    }

    return Dataset(splitedColumnNames, splitedContents, rules);
}

Pair<Dataset> Dataset::split(double ratio) const
{
    std::vector<int> indexes;
    while (indexes.size() < (int)std::round(_contents.size() * ratio))
    {
        int selectedIndex = Random::randomInteger(_contents.size());
        if (std::find(indexes.begin(), indexes.end(), selectedIndex) == indexes.end())
        {
            indexes.emplace_back(selectedIndex);
        }
    }

    std::vector<std::vector<std::string>> firstContents;
    std::vector<std::vector<std::string>> secondContents;
    for (int i = 0; i < _contents.size(); ++i)
    {
        if (std::find(indexes.begin(), indexes.end(), i) != indexes.end())
        {
            firstContents.emplace_back(_contents[i]);
        }
        else
        {
            secondContents.emplace_back(_contents[i]);
        }
    }

    return Pair<Dataset>(Dataset(_names, firstContents, _rules),
                         Dataset(_names, secondContents, _rules));
}

NormalizedDataset Dataset::normalize() const
{
    std::vector<std::vector<double>> normalizedContents;

    for (size_t row = 0; row < _contents.size(); ++row)
    {
        normalizedContents.emplace_back();
        for (size_t col = 0; col < _contents[row].size(); ++col)
        {
            std::string colName = _names[col];
            if (_rules.find(colName) != _rules.end())
            {
                NormalizeRule rule = _rules.at(colName);
                normalizedContents[row].emplace_back(Normalizer::normalize(rule, _contents[row][col]));
            }
        }
    }
    return NormalizedDataset(_names, normalizedContents);
}

DataType Dataset::type(int col)
{
    return type(_names[col]);
}

DataType Dataset::type(const std::string &colName)
{
    if (_rules.find(colName) != _rules.end())
    {
        return _rules.at(colName).type;
    }
    else
    {
        return DataType::UNDEFINED;
    }
}
std::vector<std::string> Dataset::rowData(const std::string &colName) const
{
    int index = this->colIndex(colName);
    if (index >= 0)
    {
        return rowData(index);
    }
    else
    {
        return {};
    }
}

std::vector<std::string> Dataset::rowData(int row) const
{
    std::vector<std::string> data;
    for (size_t col = 0; col < _contents.size(); ++col)
    {
        data.emplace_back(_contents[col][row]);
    }
    return data;
}