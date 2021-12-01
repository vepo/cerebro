#include "cmd/parameters.hpp"
#include <string>
#include <iostream>
#include <sstream>

void Parameters::parse(std::vector<std::string> argv,
                       const std::vector<ParamOption> &options)
{
    std::string outpuFile;
    std::string datasetFile;
    std::vector<std::string> inputNames;
    std::vector<std::string> outputNames;
    std::vector<int> layers;
    int epochs = -1;
    for (size_t index = 0; index < argv.size(); ++index)
    {
        bool processed = false;
        for (const auto &opt : options)
        {
            if (!processed)
            {
                if (opt.type == OptionType::STRING &&
                    (argv[index] == opt.shortOpt || argv[index] == opt.longOpt) &&
                    index + 1 < argv.size())
                {
                    *((std::string *)opt.dest) = argv[index + 1];
                    ++index;
                    processed = true;
                }
                else if (opt.type == OptionType::STRING_LIST &&
                         (argv[index] == opt.shortOpt || argv[index] == opt.longOpt) &&
                         index + 1 < argv.size())
                {
                    std::istringstream sstream(argv[index + 1]);
                    for (std::string key; std::getline(sstream, key, ',');)
                    {
                        ((std::vector<std::string> *)opt.dest)->push_back(key);
                    }
                    ++index;
                    processed = true;
                }
                else if (opt.type == OptionType::INTEGER_LIST &&
                         (argv[index] == opt.shortOpt || argv[index] == opt.longOpt) &&
                         index + 1 < argv.size())
                {
                    std::istringstream sstream(argv[index + 1]);
                    for (std::string layerSize; std::getline(sstream, layerSize, ',');)
                    {
                        ((std::vector<int> *)opt.dest)->push_back(std::stoi(layerSize));
                    }
                    ++index;
                    processed = true;
                }
                else if (opt.type == OptionType::INTEGER &&
                         (argv[index] == opt.shortOpt || argv[index] == opt.longOpt) &&
                         index + 1 < argv.size())
                {
                    *((int *)opt.dest) = std::stoi(argv[index + 1]);
                    ++index;
                    processed = true;
                }
            }
        }
        if (!processed)
        {
            std::cerr << "Unknown parameter: " << argv[index] << std::endl;
        }
    }
}