#pragma once

#include <vector>

#include "perceptron.hpp"

class MultiLayerPerceptron
{
public:
    MultiLayerPerceptron(std::vector<int> layers,
                         double bias = 1.0,
                         double learning_rate = 0.5,
                         double momentum = 0.7);
    void set_weights(std::vector<std::vector<std::vector<double>>> w_init);
    void print_weights();
    std::vector<double> run(std::vector<double> x);
    double bp(std::vector<double> x, std::vector<double> y);

    std::vector<int> layers;
    double bias;
    double learning_rate;
    double momentum;
    std::vector<std::vector<Perceptron>> network;
    std::vector<std::vector<double>> values;
    std::vector<std::vector<double>> network_error;
};