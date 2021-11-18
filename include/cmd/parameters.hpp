#pragma once

#include <string>
#include <vector>

class Parameters
{
public:
    static Parameters parse(std::vector<std::string> argv);
    const std::string &outpuFile() { return _outpuFile; };
    const std::string &datasetFile() { return _datasetFile; };
    const std::vector<std::string> &inputNames() { return _inputNames; };
    const std::vector<std::string> &outputNames() { return _outputNames; };
    const std::vector<int> &layers() { return _layers; };

private:
    Parameters(const std::string &outpuFile,
               const std::string &datasetFile,
               const std::vector<std::string> &inputNames,
               const std::vector<std::string> &outputNames,
               const std::vector<int> &layers);
    std::string _outpuFile;
    std::string _datasetFile;
    std::vector<std::string> _inputNames;
    std::vector<std::string> _outputNames;
    std::vector<int> _layers;
};