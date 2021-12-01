#pragma once

#include <vector>
#include <string>

enum class OptionType
{
    INTEGER = 1,
    INTEGER_LIST = 2,
    STRING = 3,
    STRING_LIST = 4
};

struct ParamOption
{
    std::string longOpt;
    std::string shortOpt;
    OptionType type;
    void *dest;
};

struct TrainerParameters
{
    std::string outpuFile;
    std::string datasetFile;
    std::vector<std::string> inputNames;
    std::vector<std::string> outputNames;
    std::vector<int> layers;
    int epochs;
};

class Parameters
{
public:
    static void parse(std::vector<std::string> argv,
                      const std::vector<ParamOption> &options);
};
