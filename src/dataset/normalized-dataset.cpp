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
NormalizedDataset::NormalizedDataset(std::vector<std::string> names,
                                     std::vector<std::vector<std::string>> contents)
{
    this->names = names;
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

        this->types.emplace_back(supposedType);

        switch (supposedType)
        {
        case DataType::STRING:
            this->contents.emplace_back(std::vector<double>());
            break;
        case DataType::INTEGER:
            this->contents.emplace_back(normalizeInteger(contents, column));
            break;
        case DataType::FLOATING_POINT:
            this->contents.emplace_back(normalizeFloatingPoint(contents, column));
            break;
        case DataType::ENUM:
            this->contents.emplace_back(normalizeEnum(contents, column));
            break;
        case DataType::BOOLEAN:
            this->contents.emplace_back(normalizeBoolean(contents, column));
            break;
        case DataType::TEXT:
            this->contents.emplace_back(std::vector<double>());
            break;
        }
    }
}

int NormalizedDataset::colIndex(std::string colName)
{
    auto it = std::find(this->names.begin(), this->names.end(), colName);
    if (it != this->names.end())
    {
        return it - this->names.begin();
    }
    else
    {
        return -1;
    }
}

double NormalizedDataset::cell(int row,
                               int col)
{
    if (contents.size() > col && contents[col].size() > row)
    {
        return contents[col][row];
    }
    else
    {
        return 0.0;
    }
}

double NormalizedDataset::cell(int row,
                               std::string colName)
{
    int colIndex = this->colIndex(colName);
    if (colIndex >= 0 && contents.size() > colIndex && contents[colIndex].size() > row)
    {
        return contents[colIndex][row];
    }
    else
    {
        return 0.0;
    }
}

DataType NormalizedDataset::type(int col)
{
    return this->types[col];
}

DataType NormalizedDataset::type(std::string colName)
{
    auto it = std::find(this->names.begin(), this->names.end(), colName);
    if (it != this->names.end())
    {
        return type(it - this->names.begin());
    }
    else
    {
        return DataType::INTEGER;
    }
}

std::vector<double> NormalizedDataset::normalizeInteger(std::vector<std::vector<std::string>> contents,
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

std::vector<double> NormalizedDataset::normalizeEnum(std::vector<std::vector<std::string>> contents, int col)
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

std::vector<double> NormalizedDataset::normalizeFloatingPoint(std::vector<std::vector<std::string>> contents, int col)
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

std::vector<double> NormalizedDataset::normalizeBoolean(std::vector<std::vector<std::string>> contents, int col)
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