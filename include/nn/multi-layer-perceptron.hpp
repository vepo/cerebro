#pragma once

#include <vector>

#include "perceptron.hpp"

class MultiLayerPerceptron
{
public:
    MultiLayerPerceptron(std::vector<std::vector<std::vector<double>>> weights,
                         double bias = 1.0);
    std::vector<double> run(std::vector<double> x);

private:
    std::vector<std::vector<Perceptron>> network;
};