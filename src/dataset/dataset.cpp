#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <random>
#include "utils/string-utils.hpp"

#include "dataset/dataset.hpp"
#include "utils/csv-reader.hpp"
#include "utils/debug.hpp"
#include "utils/random.hpp"

Dataset::Dataset(std::string const &path)
{
    this->cols = this->rows = 0;
    CSVReader reader(path);

    int counter = 0;
    while (reader.hasNextToken())
    {
        if (!counter)
        {
            this->names.emplace_back(reader.nextToken());
            this->cols++;
        }
        else
        {
            if (reader.endOfLine())
            {
                this->contents.emplace_back();
            }
            this->contents[counter - 1].emplace_back(reader.nextToken());
        }

        if (reader.endOfLine())
        {
            counter++;
        }
    }
    this->rows = counter - 1;
}

Dataset::Dataset(const std::vector<std::string> &names,
                 const std::vector<std::vector<std::string>> &contents)
    : names(names),
      contents(contents),
      cols(names.size()),
      rows(contents.size())
{
}

std::string Dataset::cell(int row, int col)
{
    return contents[row][col];
}

int Dataset::colIndex(const std::string &colName)
{
    auto it = std::find(this->names.begin(), this->names.end(), colName);
    if (it != this->names.end())
    {
        return (int)(it - this->names.begin());
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
        return contents[row][colIndex];
    }
    else
    {
        return "";
    }
}

Dataset Dataset::split(const std::vector<std::string> &columnNames)
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

Dataset Dataset::split(const std::vector<int> &colums)
{
    std::vector<std::string> splitedColumnNames;
    std::vector<std::vector<std::string>> splitedContents;
    auto initialize_row = [=, &splitedContents](auto &__)
    { splitedContents.emplace_back(); };
    std::for_each(this->contents.cbegin(), this->contents.cend(), initialize_row);

    for (const auto &index : colums)
    {
        splitedColumnNames.emplace_back(this->names[index]);
        for (size_t row = 0; row < this->contents.size(); ++row)
        {
            splitedContents[row].emplace_back(this->contents[row][index]);
        }
    }
    return Dataset(splitedColumnNames, splitedContents);
}

Pair<Dataset> Dataset::split(double ratio)
{
    std::vector<int> indexes;
    while (indexes.size() < (int)std::round(this->contents.size() * ratio))
    {
        int selectedIndex = Random::randomInteger() % this->contents.size();
        if (std::find(indexes.begin(), indexes.end(), selectedIndex) == indexes.end())
        {
            indexes.emplace_back(selectedIndex);
        }
    }

    std::vector<std::vector<std::string>> firstContents;
    std::vector<std::vector<std::string>> secondContents;
    for (int i = 0; i < this->contents.size(); ++i)
    {
        if (std::find(indexes.begin(), indexes.end(), i) != indexes.end())
        {
            firstContents.emplace_back(this->contents[i]);
        }
        else
        {
            secondContents.emplace_back(this->contents[i]);
        }
    }

    return Pair<Dataset>(Dataset(this->names, firstContents),
                         Dataset(this->names, secondContents));
}

NormalizedDataset Dataset::normalize()
{
    return NormalizedDataset(this->names, this->contents);
}