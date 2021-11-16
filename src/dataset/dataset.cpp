#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
#include "utils/string-utils.hpp"

#include "dataset/dataset.hpp"
#include "utils/csv-reader.hpp"
#include "utils/debug.hpp"

Dataset::Dataset(string path)
{
    this->cols = this->rows = 0;
    CSVReader reader(path);

    int counter = 0;
    while (reader.hasNextToken())
    {
        if (!counter)
        {
            this->names.push_back(reader.nextToken());
            this->cols++;
        }
        else
        {
            if (reader.endOfLine())
            {
                this->contents.push_back(vector<string>());
            }
            this->contents[counter - 1].push_back(reader.nextToken());
        }

        if (reader.endOfLine())
        {
            counter++;
        }
    }
    this->rows = counter - 1;
}

Dataset::Dataset(vector<string> names, vector<vector<string>> contents)
{
    this->names = names;
    this->contents = contents;
    this->cols = names.size();
    this->rows = contents.size();
}

string Dataset::cell(int row, int col)
{
    return contents[row][col];
}

int Dataset::colIndex(string colName)
{
    auto it = find(this->names.begin(), this->names.end(), colName);
    if (it != this->names.end())
    {
        return it - this->names.begin();
    }
    else
    {
        return -1;
    }
}

string Dataset::cell(int row, string colName)
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

Dataset Dataset::split(vector<string> columnNames)
{
    vector<int> columns;
    for (auto columnName : columnNames)
    {
        int index = this->colIndex(columnName);
        if (index >= 0)
        {
            columns.push_back(index);
        }
    }
    return this->split(columns);
}

Dataset Dataset::split(vector<int> colums)
{
    vector<string> columnNames;
    vector<vector<string>> contents;
    for (size_t row = 0; row < this->contents.size(); ++row)
    {
        contents.push_back(vector<string>());
    }

    for (auto index : colums)
    {
        columnNames.push_back(this->names[index]);
        for (size_t row = 0; row < this->contents.size(); ++row)
        {
            contents[row].push_back(this->contents[row][index]);
        }
    }
    Dataset inner(columnNames, contents);
    return inner;
}

Pair<Dataset> Dataset::split(double ratio)
{
    vector<int> indexes;
    while (indexes.size() < (int)(this->contents.size() * ratio))
    {
        int selectedIndex = rand() % this->contents.size();
        if (find(indexes.begin(), indexes.end(), selectedIndex) == indexes.end())
        {
            indexes.push_back(selectedIndex);
        }
    }

    vector<vector<string>> firstContents;
    vector<vector<string>> secondContents;
    for (int i = 0; i < this->contents.size(); ++i)
    {
        if (find(indexes.begin(), indexes.end(), i) == indexes.end())
        {
            firstContents.push_back(this->contents[i]);
        }
        else
        {
            secondContents.push_back(this->contents[i]);
        }
    }

    return Pair<Dataset>(Dataset(this->names, firstContents),
                         Dataset(this->names, secondContents));
}

NormalizedDataset Dataset::normalize()
{
    NormalizedDataset nd(this->names, this->contents);
    return nd;
}