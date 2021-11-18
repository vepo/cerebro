#pragma once

#include <vector>
#include <string>

enum class DataType
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
    std::vector<double> normalizeInteger(std::vector<std::vector<std::string>> contents, int col);
    std::vector<double> normalizeEnum(std::vector<std::vector<std::string>> contents, int col);
    std::vector<double> normalizeFloatingPoint(std::vector<std::vector<std::string>> contents, int col);
    std::vector<double> normalizeBoolean(std::vector<std::vector<std::string>> contents, int col);
    int colIndex(std::string colName);
    std::vector<std::string> names;
    std::vector<std::vector<double>> contents;
    std::vector<DataType> types;
    static std::vector<std::string> TRUE_VALUES;
    static std::vector<std::string> FALSE_VALUES;
};