#pragma once

#include <vector>

#include "perceptron.hpp"

class MultiLayerPerceptronTrainee
{
public:
    MultiLayerPerceptronTrainee(std::vector<int> layers,
                                double bias = 1.0,
                                double learning_rate = 0.5,
                                double momentum = 0.7,
                                double dropout = 0.2);
    void setWeights(std::vector<std::vector<std::vector<double>>> w_init);
    std::vector<std::vector<std::vector<double>>> get_weights();
    void printWeights();
    std::vector<double> run(std::vector<double> x);
    double bp(std::vector<double> x, std::vector<double> y);
    void generateDropout();
    void disableDropout();
    double bias() const { return _bias; };

private:
    std::vector<int> _layers;
    double _bias;
    double _learning_rate;
    double _momentum;
    double _dropout;
    std::vector<std::vector<Perceptron>> _network;
    std::vector<std::vector<double>> _values;
    std::vector<std::vector<bool>> _droppedValues;
    std::vector<std::vector<double>> _network_error;
};