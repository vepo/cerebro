#pragma once

#include <vector>
#include <string>

enum DataType
{
    STRING = 1,
    INTEGER = 2,
    FLOATING_POINT = 3,
    ENUM = 4,
    BOOLEAN = 5,
    TEXT = 6
};

class NormalizedDataset
{
public:
    NormalizedDataset(std::vector<std::string> names,
                      std::vector<std::vector<std::string>> contents);
    double cell(int row, int col);
    double cell(int row, std::string colName);
    DataType type(int col);
    DataType type(std::string colName);

private:
    std::vector<std::string> names;
    std::vector<std::vector<double>> contents;
    std::vector<DataType> types;
};