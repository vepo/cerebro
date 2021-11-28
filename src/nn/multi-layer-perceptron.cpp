#include "nn/multi-layer-perceptron.hpp"
#include <iostream>
#include <iomanip>

MultiLayerPerceptron::MultiLayerPerceptron(std::vector<std::vector<std::vector<double>>> weights,
                                           double bias)
{
    for (size_t i = 0; i < weights.size(); ++i)
    {
        network.emplace_back();
        for (int j = 0; j < weights[i].size(); ++j)
        {
            network[i ].emplace_back(Perceptron(weights[i][j], bias));
        }
    }
}

std::vector<double> MultiLayerPerceptron::run(std::vector<double> x)
{
    std::vector<double> previous = x;
    std::vector<double> current;
    for (size_t i = 0; i < network.size(); ++i)
    {
        current.clear();
        for (int j = 0; j < network[i].size(); ++j)
        {
            current.emplace_back(network[i][j].run(previous));
        }
        previous = current;
    }
    return previous;
}