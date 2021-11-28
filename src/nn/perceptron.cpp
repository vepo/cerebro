#include <algorithm>
#include <numeric>
#include <cmath>

#include "nn/perceptron.hpp"
#include "utils/random.hpp"

Perceptron::Perceptron(int inputs,
                       Function function,
                       double bias) : bias(bias),
                                      fn(resolveFunction(function))
{
    weights.resize(inputs + 1);
    std::generate(weights.begin(), weights.end(), Random::randomDouble);
}

Perceptron::Perceptron(std::vector<double> weights,
                       Function function,
                       double bias) : weights(weights),
                                      bias(bias),
                                      fn(resolveFunction(function))
{
}

double Perceptron::run(std::vector<double> x)
{
    x.push_back(bias);
    double sum = std::inner_product(x.begin(), x.end(), weights.begin(), (double)0.0);
    return (*fn)(sum);
}

void Perceptron::setWeights(std::vector<double> w_init)
{
    weights = w_init;
}

double Perceptron::sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

double Perceptron::identity(double x)
{
    return x;
}

perceptronFunction Perceptron::resolveFunction(Function fn)
{
    switch (fn)
    {
    case Function::SIGMOID:
        return Perceptron::sigmoid;
    case Function::IDENTITY:
    default:
        return Perceptron::identity;
    }
}