#include <limits>
#include <cmath>

#include "utils/string-utils.hpp"
#include "dataset/dataset.hpp"
#include "utils/csv-reader.hpp"
#include "utils/random.hpp"

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
}
Dataset::Dataset(const Dataset &src) : _names(src._names),
                                       _contents(src._contents),
                                       _cols(src._cols),
                                       _rows(src._rows)
{
}

Dataset::Dataset(const std::vector<std::string> &names,
                 const std::vector<std::vector<std::string>> &contents)
    : _names(names),
      _contents(contents),
      _cols(names.size()),
      _rows(contents.size())
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

    for (const auto &index : colums)
    {
        splitedColumnNames.emplace_back(_names[index]);
        for (size_t row = 0; row < _contents.size(); ++row)
        {
            splitedContents[row].emplace_back(_contents[row][index]);
        }
    }
    return Dataset(splitedColumnNames, splitedContents);
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

    return Pair<Dataset>(Dataset(_names, firstContents),
                         Dataset(_names, secondContents));
}

NormalizedDataset Dataset::normalize() const
{
    return NormalizedDataset(_names, _contents);
}