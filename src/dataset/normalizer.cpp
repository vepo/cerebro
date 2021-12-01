#include "dataset/normalizer.hpp"

std::regex Normalizer::INTEGER_PATTERN("\\s*-?\\s*[0-9]+\\s*");
std::regex Normalizer::FLOATING_POINT_PATTERN("\\s*-?\\s*[0-9]*\\.[0-9]*\\s*");
std::regex Normalizer::ENUM_PATTERN("\\s*[A-Za-z0-9\\s]+\\s*");

std::vector<std::string> Normalizer::TRUE_VALUES = {"t", "true", "s", "sim"};
std::vector<std::string> Normalizer::FALSE_VALUES = {"f", "false", "n", "não", "nao"};

DataType Normalizer::inferType(const std::vector<std::string> &data,
                               std::set<std::string> *uniqueValues)
{
    bool localSet = nullptr == uniqueValues;
    if (localSet)
    {
        uniqueValues = new std::set<std::string>();
    }

    DataType supposedType = DataType::INTEGER;
    for (int row = 0; row < data.size(); row++)
    {
        if (data[row].size() > 0)
        {
            uniqueValues->insert(data[row]);
            if (supposedType == DataType::INTEGER &&
                regex_match(data[row], INTEGER_PATTERN))
            {
                continue;
            }
            else if ((supposedType == DataType::INTEGER ||
                      supposedType == DataType::FLOATING_POINT) &&
                     (regex_match(data[row], FLOATING_POINT_PATTERN) ||
                      regex_match(data[row], INTEGER_PATTERN)))
            {
                supposedType = DataType::FLOATING_POINT;
            }
            else if (regex_match(data[row], ENUM_PATTERN))
            {
                supposedType = DataType::ENUM;
            }
            else
            {
                supposedType = DataType::UNDEFINED;
            }
        }
    }
    if (supposedType == DataType::ENUM && uniqueValues->size() <= 2)
    {
        supposedType = DataType::BOOLEAN;
    }

    if (localSet)
    {
        delete uniqueValues;
    }

    return supposedType;
}

NormalizeRule Normalizer::inferRule(const std::vector<std::string> &data)
{
    std::set<std::string> uniqueValues;
    DataType supposedType = inferType(data, &uniqueValues);
    if (supposedType == DataType::INTEGER || supposedType == DataType::FLOATING_POINT)
    {

        double min = std::numeric_limits<double>::max();
        double max = std::numeric_limits<double>::min();

        for (int row = 0; row < data.size(); ++row)
        {
            switch (supposedType)
            {
            case DataType::INTEGER:
            {
                int iValue = std::stoi(data[row]);
                if (min > iValue)
                {
                    min = iValue;
                }
                if (max < iValue)
                {
                    max = iValue;
                }
            }
            break;
            case DataType::FLOATING_POINT:
            {
                double fpValue = std::stod(data[row]);
                if (min > fpValue)
                {
                    min = fpValue;
                }
                if (max < fpValue)
                {
                    max = fpValue;
                }
            }
            break;
            default:
                break;
            }
        }
        return {.type = supposedType, .min = min, .max = max, .values = {}};
    }
    else
    {
        return {.type = supposedType, .min = 0.0, .max = 0.0, .values = {uniqueValues.begin(), uniqueValues.end()}};
    }
}

double Normalizer::normalize(const NormalizeRule &rule, const std::string &value)
{
    switch (rule.type)
    {
    case DataType::INTEGER:
    {

        return normalizeFloatPoint(value, rule.min, rule.max);
    };
    case DataType::FLOATING_POINT:
    {
        return normalizeFloatPoint(value, rule.min, rule.max);
    };
    case DataType::ENUM:
    {
        return normalizeEnum(value, rule.values);
    }
    case DataType::BOOLEAN:
        return normalizeBoolean(value, rule.values);
    default:
        return 0.0;
    }
}
double Normalizer::normalizeInteger(const std::string &value,
                                    int min, int max)
{
    if (max != min)
    {
        return ((double)std::stoi(value) - min) / (max - min);
    }
    else
    {
        return 0.0;
    }
}

double Normalizer::normalizeFloatPoint(const std::string &value,
                                       double min, double max)
{
    if (max != min)
    {
        return (std::stod(value) - min) / (max - min);
    }
    else
    {
        return 0.0;
    }
}

double Normalizer::normalizeEnum(const std::string &value,
                                 const std::vector<std::string> &values)
{
    auto index = std::find(values.begin(), values.end(), value);
    if (values.size() > 0 && index != values.end())
    {
        return ((double)(index - values.begin() + 1)) / ((double)values.size());
    }
    else
    {
        return 0.0;
    }
}

double Normalizer::normalizeBoolean(const std::string &value,
                                    const std::vector<std::string> &values)
{
    if (std::find(TRUE_VALUES.begin(), TRUE_VALUES.end(), value) != TRUE_VALUES.end())
    {
        return 1.0;
    }
    else if (std::find(FALSE_VALUES.begin(), FALSE_VALUES.end(), value) != FALSE_VALUES.end())
    {
        return 0.5;
    }
    else if (values.size() == 2 && values[0] == value)
    {
        return 1.0;
    }
    else if (values.size() == 2 && values[1] == value)
    {
        return 0.5;
    }
    else
    {
        return 0.0;
    }
}