#include "cmd/parameters.hpp"
#include <string>
#include <iostream>
#include <sstream>

const ParamOption *findOption(const std::string &name,
                              const std::vector<ParamOption> &options)
{
    for (const auto &opt : options)
    {
        if (opt.shortOpt == name || opt.longOpt == name)
        {
            return &opt;
        }
    }
    return nullptr;
}

void Parameters::parse(std::vector<std::string> argv,
                       const std::vector<ParamOption> &options)
{
    for (size_t index = 0; index < argv.size(); ++index)
    {
        const ParamOption *opt = findOption(argv[index], options);
        if (nullptr != opt)
        {
            if (index + 1 < argv.size())
            {
                switch (opt->type)
                {
                case OptionType::INTEGER:
                {
                    *((int *)opt->dest) = std::stoi(argv[index + 1]);
                    ++index;
                }
                break;
                case OptionType::INTEGER_LIST:
                {
                    std::istringstream sstream(argv[index + 1]);
                    for (std::string layerSize; std::getline(sstream, layerSize, ',');)
                    {
                        ((std::vector<int> *)opt->dest)->push_back(std::stoi(layerSize));
                    }
                    ++index;
                }
                break;
                case OptionType::STRING:
                {
                    *((std::string *)opt->dest) = argv[index + 1];
                    ++index;
                }
                break;
                case OptionType::STRING_LIST:
                {
                    std::istringstream sstream(argv[index + 1]);
                    for (std::string key; std::getline(sstream, key, ',');)
                    {
                        ((std::vector<std::string> *)opt->dest)->push_back(key);
                    }
                    ++index;
                }
                break;
                default:
                    break;
                }
            }
        }
        else
        {
            std::cerr << "Unknown parameter: " << argv[index] << std::endl;
        }
    }
}