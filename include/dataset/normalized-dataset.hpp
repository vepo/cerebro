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
    NormalizedDataset(const std::vector<std::string> &names,
                      const std::vector<std::vector<std::string>> &contents);
    double cell(int row, int col);
    double cell(int row, const std::string &colName);
    DataType type(int col);
    DataType type(const std::string &colName);

private:
    static std::vector<double> normalizeInteger(const std::vector<std::vector<std::string>> &contents, int col);
    static std::vector<double> normalizeEnum(const std::vector<std::vector<std::string>> &contents, int col);
    static std::vector<double> normalizeFloatingPoint(const std::vector<std::vector<std::string>> &contents, int col);
    static std::vector<double> normalizeBoolean(const std::vector<std::vector<std::string>> &contents, int col);
    int colIndex(const std::string &colName);
    std::vector<std::string> _names;
    std::vector<std::vector<double>> _contents;
    std::vector<DataType> _types;
    static std::vector<std::string> TRUE_VALUES;
    static std::vector<std::string> FALSE_VALUES;
};