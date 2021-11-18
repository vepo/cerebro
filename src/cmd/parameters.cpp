#include "cmd/parameters.hpp"
#include <string>
#include <iostream>
#include <sstream>

Parameters Parameters::parse(std::vector<std::string> argv)
{
    std::string outpuFile;
    std::string datasetFile;
    std::vector<std::string> inputNames;
    std::vector<std::string> outputNames;
    std::vector<int> layers;

    for (size_t index = 0; index < argv.size(); ++index)
    {
        if ((argv[index] == "-o" || argv[index] == "--output-file") &&
            index + 1 < argv.size())
        {
            outpuFile = argv[index + 1];
            index++;
        }
        else if ((argv[index] == "-d" || argv[index] == "--dataset") &&
                 index + 1 < argv.size())
        {
            datasetFile = argv[index + 1];
            ++index;
        }
        else if ((argv[index] == "-in" || argv[index] == "--input") &&
                 index + 1 < argv.size())
        {
            std::istringstream sstream(argv[index + 1]);
            for (std::string key; std::getline(sstream, key, ',');)
            {
                inputNames.push_back(key);
            }
            ++index;
        }
        else if ((argv[index] == "-out" || argv[index] == "--output") &&
                 index + 1 < argv.size())
        {
            std::istringstream sstream(argv[index + 1]);
            for (std::string key; std::getline(sstream, key, ',');)
            {
                outputNames.push_back(key);
            }
            ++index;
        }
        else if ((argv[index] == "-l" || argv[index] == "--layers") &&
                 index + 1 < argv.size())
        {
            std::istringstream sstream(argv[index + 1]);
            for (std::string layerSize; std::getline(sstream, layerSize, ',');)
            {
                layers.push_back(std::stoi(layerSize));
            }
            ++index;
        }
        else
        {
            std::cerr << "Unknown parameter: " << argv[index] << std::endl;
        }
    }

    return Parameters(outpuFile, datasetFile, inputNames, outputNames, layers);
}

Parameters::Parameters(const std::string &outpuFile,
                       const std::string &datasetFile,
                       const std::vector<std::string> &inputNames,
                       const std::vector<std::string> &outputNames,
                       const std::vector<int> &layers) : _outpuFile(outpuFile),
                                                         _datasetFile(datasetFile),
                                                         _inputNames(inputNames),
                                                         _outputNames(outputNames),
                                                         _layers(layers)
{
}