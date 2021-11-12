#include <fstream>
#include <sstream>
#include <algorithm>

#include "dataset/dataset.hpp"

Dataset::Dataset(string path)
{
    this->path = path;
    this->cols = this->rows = 0;
    ifstream input_file(path);
    if (!input_file.is_open())
    {
        exit(EXIT_FAILURE);
    }
    int counter = 0;
    string record;
    while (getline(input_file, record))
    {
        istringstream line(record);
        while (getline(line, record, ','))
        {
            if (!counter)
            {
                this->names.push_back(record);
                this->cols++;
            }
            else
            {
                if (counter + 1 > (int)this->contents.size())
                {
                    this->contents.push_back(vector<string>());
                }
                this->contents[counter - 1].push_back(record);
            }
        }
        counter += 1;
    }
    this->rows = counter - 1;
    input_file.close();
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