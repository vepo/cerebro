#include "dataset/normalized-dataset.hpp"
#include <iostream>
#include <regex>
#include <set>
#include <limits>
#include <string>

std::vector<std::string> NormalizedDataset::TRUE_VALUES = {"t", "true", "s", "sim"};
std::vector<std::string> NormalizedDataset::FALSE_VALUES = {"f", "false", "n", "não", "nao"};

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
NormalizedDataset::NormalizedDataset(const std::vector<std::string> &names,
                                     const std::vector<std::vector<std::string>> &contents) : _names(names)
{
    std::regex integerPattern("\\s*-?\\s*[0-9]+\\s*");
    std::regex floatingPointPattern("\\s*-?\\s*[0-9]*\\.[0-9]*\\s*");
    std::regex enumPattern("\\s*[A-Za-z0-9\\s]+\\s*");

    for (int column = 0; column < names.size(); column++)
    {
        DataType supposedType = DataType::INTEGER;
        std::set<std::string> uniqueValues;
        for (int row = 0; row < contents.size(); row++)
        {
            if (contents[row][column].size() > 0)
            {
                uniqueValues.insert(contents[row][column]);
                if (supposedType == DataType::INTEGER &&
                    regex_match(contents[row][column], integerPattern))
                {
                    continue;
                }
                else if ((supposedType == DataType::INTEGER ||
                          supposedType == DataType::FLOATING_POINT) &&
                         (regex_match(contents[row][column], floatingPointPattern) ||
                          regex_match(contents[row][column], integerPattern)))
                {
                    supposedType = DataType::FLOATING_POINT;
                }
                else if (regex_match(contents[row][column], enumPattern))
                {
                    supposedType = DataType::ENUM;
                }
            }
        }
        if (supposedType == DataType::ENUM && uniqueValues.size() <= 2)
        {
            supposedType = DataType::BOOLEAN;
        }
        else if (supposedType == DataType::ENUM && uniqueValues.size() > contents.size() / 2)
        {
            supposedType = DataType::STRING;
        }

        _types.emplace_back(supposedType);

        switch (supposedType)
        {
        case DataType::STRING:
            _contents.emplace_back();
            break;
        case DataType::INTEGER:
            _contents.emplace_back(normalizeInteger(contents, column));
            break;
        case DataType::FLOATING_POINT:
            _contents.emplace_back(normalizeFloatingPoint(contents, column));
            break;
        case DataType::ENUM:
            _contents.emplace_back(normalizeEnum(contents, column));
            break;
        case DataType::BOOLEAN:
            _contents.emplace_back(normalizeBoolean(contents, column));
            break;
        case DataType::TEXT:
        default:
            _contents.emplace_back();
            break;
        }
    }
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
    if (_contents.size() > col && _contents[col].size() > row)
    {
        return _contents[col][row];
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
        _contents.size() > colIndex &&
        _contents[colIndex].size() > row)
    {
        return _contents[colIndex][row];
    }
    else
    {
        return 0.0;
    }
}

std::vector<double> NormalizedDataset::rowData(int row) const
{
    std::vector<double> data;
    for (size_t col = 0; col < _contents.size(); ++col)
    {
        data.emplace_back(_contents[col][row]);
    }
    return data;
}

DataType NormalizedDataset::type(int col)
{
    return _types[col];
}

DataType NormalizedDataset::type(const std::string &colName)
{
    auto it = std::find(_names.begin(), _names.end(), colName);
    if (it != _names.end())
    {
        return type(it - _names.begin());
    }
    else
    {
        return DataType::INTEGER;
    }
}

std::vector<double> NormalizedDataset::normalizeInteger(const std::vector<std::vector<std::string>> &contents,
                                                        int col)
{
    int min = std::numeric_limits<int>::max();
    int max = std::numeric_limits<int>::min();
    std::vector<int> values;
    for (int row = 0; row < contents.size(); ++row)
    {
        int value = std::stoi(contents[row][col]);

        values.emplace_back(value);

        if (value > max)
        {
            max = value;
        }

        if (value < min)
        {
            min = value;
        }
    }

    std::vector<double> normalizedValues;
    for (int row = 0; row < contents.size(); ++row)
    {
        normalizedValues.emplace_back(((double)values[row] - (double)min) /
                                      ((double)max - (double)min));
    }
    return normalizedValues;
}

std::vector<double> NormalizedDataset::normalizeEnum(const std::vector<std::vector<std::string>> &contents,
                                                     int col)
{
    std::vector<std::string> loadedValues;
    std::vector<int> values;
    for (int row = 0; row < contents.size(); ++row)
    {
        auto index = std::find(loadedValues.begin(), loadedValues.end(), contents[row][col]);
        if (index == loadedValues.end())
        {
            values.emplace_back(loadedValues.size());
            loadedValues.emplace_back(contents[row][col]);
        }
        else
        {
            values.emplace_back(index - loadedValues.begin());
        }
    }
    std::vector<double> normalizedValues;
    for (int row = 0; row < contents.size(); ++row)
    {
        normalizedValues.emplace_back((double)values[row] /
                                      ((double)loadedValues.size() - (double)1));
    }
    return normalizedValues;
}

std::vector<double> NormalizedDataset::normalizeFloatingPoint(const std::vector<std::vector<std::string>> &contents,
                                                              int col)
{
    double min = std::numeric_limits<double>::max();
    double max = std::numeric_limits<double>::min();
    std::vector<double> values;
    for (int row = 0; row < contents.size(); ++row)
    {
        double value = std::stod(contents[row][col]);

        values.emplace_back(value);

        if (value > max)
        {
            max = value;
        }

        if (value < min)
        {
            min = value;
        }
    }

    std::vector<double> normalizedValues;
    for (int row = 0; row < contents.size(); ++row)
    {
        normalizedValues.emplace_back(((double)values[row] - (double)min) /
                                      ((double)max - (double)min));
    }
    return normalizedValues;
}

std::vector<double> NormalizedDataset::normalizeBoolean(const std::vector<std::vector<std::string>> &contents,
                                                        int col)
{
    std::string trueValue;
    std::string falseValue;

    std::vector<bool> values;
    for (int row = 0; row < contents.size(); ++row)
    {
        std::string value = contents[row][col];
        if (!trueValue.empty() && trueValue == value)
        {
            values.emplace_back(true);
        }
        else if (!falseValue.empty() && falseValue == value)
        {
            values.emplace_back(false);
        }
        else if (std::find(TRUE_VALUES.begin(), TRUE_VALUES.end(), value) != TRUE_VALUES.end())
        {
            trueValue = value;
            values.emplace_back(true);
        }
        else if (std::find(FALSE_VALUES.begin(), FALSE_VALUES.end(), value) != FALSE_VALUES.end())
        {
            falseValue = value;
            values.emplace_back(false);
        }
        else if (trueValue.empty())
        {
            trueValue = value;
            values.emplace_back(true);
        }
        else
        {
            falseValue = value;
            values.emplace_back(false);
        }
    }
    std::vector<double> normalizedValues;
    for (int row = 0; row < contents.size(); ++row)
    {
        normalizedValues.emplace_back(values[row] ? 1.0 : 0.0);
    }
    return normalizedValues;
}