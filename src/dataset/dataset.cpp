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
    this->path = path;
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
            if (counter + 1 > (int)this->contents.size())
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
    //DEBUG("Cols: " << this->cols)
    //DEBUG("Rows: " << this->rows)
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