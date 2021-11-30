#include "dataset/normalized-dataset.hpp"
#include <iostream>
#include <regex>
#include <set>
#include <limits>
#include <string>
#include <iomanip>

NormalizedDataset::NormalizedDataset(const std::vector<std::string> &names,
                                     const std::vector<std::vector<double>> &contents) : _names(names),
                                                                                         _contents(contents)
{
}

int NormalizedDataset::colIndex(const std::string &colName)
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

double NormalizedDataset::cell(int row,
                               int col)
{
    if (_contents.size() > row && _contents[row].size() > col)
    {
        return _contents[row][col];
    }
    else
    {
        return 0.0;
    }
}

double NormalizedDataset::cell(int row,
                               const std::string &colName)
{
    int colIndex = this->colIndex(colName);
    if (colIndex >= 0 &&
        _contents.size() > row &&
        _contents[row].size() > colIndex)
    {
        return _contents[row][colIndex];
    }
    else
    {
        return 0.0;
    }
}

std::vector<double> NormalizedDataset::rowData(int row) const
{
    return _contents[row];
}

//void NormalizedDataset::printValues()
//{
//    for (int row = 0; row < _contents.size(); ++row)
//    {
//
//        for (int col = 0; col < _contents[row].size(); ++col)
//        {
//            std::cout << std::setw(10) << std::setprecision(5) << _contents[row][col] << "    ";
//        }
//        std::cout << std::endl;
//    }
//}