#pragma once

#include <vector>
#include <string>
#include <regex>
#include <set>

enum class DataType
{
    INTEGER = 1,
    FLOATING_POINT = 2,
    ENUM = 3,
    BOOLEAN = 4,
    UNDEFINED = 999
};

struct NormalizeRule
{
    DataType type;
    double min;
    double max;
    std::vector<std::string> values;
};

class Normalizer
{
public:
    static NormalizeRule inferRule(const std::vector<std::string> &data);
    static double normalize(const NormalizeRule &rule, const std::string &value);
    static DataType inferType(const std::vector<std::string> &data,
                              std::set<std::string> *uniqueValues = NULL);

private:
    static std::vector<std::string> TRUE_VALUES;
    static std::vector<std::string> FALSE_VALUES;
    static std::regex INTEGER_PATTERN;
    static std::regex FLOATING_POINT_PATTERN;
    static std::regex ENUM_PATTERN;
};