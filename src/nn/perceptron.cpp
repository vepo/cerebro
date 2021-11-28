#include <algorithm>
#include <numeric>
#include <cmath>

#include "nn/perceptron.hpp"
#include "utils/random.hpp"

Perceptron::Perceptron(int inputs, double bias)
{
    this->bias = bias;
    weights.resize(inputs + 1);
    std::generate(weights.begin(), weights.end(), Random::randomDouble);
}

Perceptron::Perceptron(std::vector<double> weights, double bias) : weights(weights),
                                                                   bias(bias)
{
}

double Perceptron::run(std::vector<double> x)
{
    x.push_back(bias);
    double sum = std::inner_product(x.begin(), x.end(), weights.begin(), (double)0.0);
    return sigmoid(sum);
}

void Perceptron::setWeights(std::vector<double> w_init)
{
    weights = w_init;
}

double Perceptron::sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}