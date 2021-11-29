#include "nn/model.hpp"

Model::Model(std::string name,
             std::vector<std::string> inputs,
             std::vector<std::string> outputs,
             std::vector<std::vector<std::vector<double>>> weights,
             double bias) : _name(name),
                            _inputs(inputs),
                            _outputs(outputs),
                            _weights(weights),
                            _bias(bias)

{
}