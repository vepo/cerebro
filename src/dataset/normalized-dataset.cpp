#include "dataset/normalized-dataset.hpp"
#include <iostream>
#include <regex>
#include <set>

/**
 * @brief Construct a new Normalized Dataset:: Normalized Dataset object
 * 
 * The big question here is how do we normalize a dataset? 
 * The first challenge finding the data type for the column, 
 * so we will supose that every column is an integer column,
 * if any of the content has a enum pattern
 * 
 * @param names column names
 * @param contents original data 
 */
NormalizedDataset::NormalizedDataset(vector<string> names,
                                     vector<vector<string>> contents)
{
    regex integerPattern("\\s*[0-9]+\\s*");
    regex floatingPointPattern("\\s*[0-9]*\\.[0-9]+\\s*");
    regex enumPattern("\\s*[A-Za-z0-9\\s]+\\s*");

    vector<DataType> types;
    for (int column = 0; column < names.size(); column++)
    {
        DataType supposedType = INTEGER;
        std::cout << "Column: " << column << std::endl;
        for (int row = 0; row < contents.size(); row++)
        {
            if (supposedType == INTEGER &&
                regex_match(contents[row][column], integerPattern))
            {
                std::cout << "Integer found: " << contents[row][column] << endl;
            }
            else if ((supposedType == INTEGER || supposedType == FLOATING_POINT) &&
                     regex_match(contents[row][column], floatingPointPattern))
            {
                supposedType = FLOATING_POINT;
                std::cout << "Floating Point found: " << contents[row][column] << endl;
            }
            else if (regex_match(contents[row][column], enumPattern))
            {
                std::cout << "Enum found: " << contents[row][column] << endl;
            }
            else
            {
                std::cout << "No Pattern found: " << contents[row][column] << endl;
            }
        }
    }
}

double NormalizedDataset::cell(int row, int col)
{
    return 0.0;
}

double NormalizedDataset::cell(int row, string colName)
{
    return 0.0;
}

DataType NormalizedDataset::type(int col)
{
    return this->types[col];
}

DataType NormalizedDataset::type(string colName)
{
    auto it = find(this->names.begin(), this->names.end(), colName);
    if (it != this->names.end())
    {
        return type(it - this->names.begin());
    }
    else
    {
        return INTEGER;
    }
}