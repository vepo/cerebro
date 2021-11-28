#pragma once

#include <vector>

enum class Function
{
    SIGMOID = 0,
    IDENTITY = 1
};

typedef double (*perceptronFunction)(double);

class Perceptron
{
public:
    Perceptron(int inputs,
               Function function = Function::SIGMOID,
               double bias = 1.0);
    Perceptron(std::vector<double> weights,
               Function function = Function::SIGMOID,
               double bias = 1.0);
    void setWeights(std::vector<double> w_init);
    std::vector<double> weights;
    double bias;
    double run(std::vector<double> x);

private:
    static perceptronFunction resolveFunction(Function fn);
    static double sigmoid(double x);
    static double identity(double x);
    perceptronFunction fn;
};