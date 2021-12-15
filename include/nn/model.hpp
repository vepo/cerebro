#pragma once

#include <string>
#include <vector>
class Model
{
public:
    static Model load(const std::string &path);
    Model(std::string name,
          std::vector<std::string> inputs,
          std::vector<std::string> outputs,
          std::vector<std::vector<std::vector<double>>> weights,
          double bias);
    bool save(const std::string &path);
    const std::string name() { return _name; };
    const std::vector<std::string> inputs() { return _inputs; };
    const std::vector<std::string> outputs() { return _outputs; };

private:
    std::string _name;
    std::vector<std::string> _inputs;
    std::vector<std::string> _outputs;
    std::vector<std::vector<std::vector<double>>> _weights;
    double _bias;
};