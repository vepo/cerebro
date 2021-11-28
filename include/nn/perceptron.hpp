#pragma once

#include <vector>

class Perceptron
{
public:
    Perceptron(int inputs, double bias = 1.0);
    Perceptron(std::vector<double> weights, double bias = 1.0);
    void setWeights(std::vector<double> w_init);
    std::vector<double> weights;
    double bias;
    double run(std::vector<double> x);
    double sigmoid(double x);
};