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
    static double normalizeBoolean(const std::string &value,
                                   const std::vector<std::string> &values);
    static double normalizeEnum(const std::string &value,
                                const std::vector<std::string> &values);
    static double normalizeFloatPoint(const std::string &value,
                                      double min, double max);
    static double normalizeInteger(const std::string &value,
                                   int min, int max);

private:
    static std::vector<std::string> TRUE_VALUES;
    static std::vector<std::string> FALSE_VALUES;
    static std::regex INTEGER_PATTERN;
    static std::regex FLOATING_POINT_PATTERN;
    static std::regex ENUM_PATTERN;
};