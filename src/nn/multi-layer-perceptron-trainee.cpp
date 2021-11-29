#include "nn/multi-layer-perceptron-trainee.hpp"
#include <iostream>
#include <iomanip>
#include "utils/random.hpp"

MultiLayerPerceptronTrainee::MultiLayerPerceptronTrainee(std::vector<int> layers,
                                                         double bias,
                                                         double learning_rate,
                                                         double momentum,
                                                         double dropout) : _layers(layers),
                                                                           _bias(bias),
                                                                           _learning_rate(learning_rate),
                                                                           _momentum(momentum),
                                                                           _dropout(dropout)
{
    for (size_t i = 0; i < layers.size(); ++i)
    {
        _values.emplace_back(std::vector<double>(layers[i], 0.0));
        _network_error.emplace_back(std::vector<double>(layers[i], 0.0));
        _network.emplace_back();
        _droppedValues.emplace_back();
        if (i > 0)
        {
            _droppedValues.emplace_back();
            for (int j = 0; j < layers[i]; ++j)
            {
                if (j != layers[i] - 1)
                {
                    _droppedValues[i - 1].emplace_back(false);
                }
                _network[i].emplace_back(Perceptron(layers[i - 1], Function::SIGMOID, bias));
            }
        }
    }
}

void MultiLayerPerceptronTrainee::setWeights(std::vector<std::vector<std::vector<double>>> w_init)
{
    for (size_t i = 0; i < w_init.size(); ++i)
    {
        for (size_t j = 0; j < w_init[i].size(); ++j)
        {
            _network[i + 1][j].setWeights(w_init[i][j]);
        }
    }
}

std::vector<std::vector<std::vector<double>>> MultiLayerPerceptronTrainee::get_weights()
{
    std::vector<std::vector<std::vector<double>>> weights;

    for (size_t i = 1; i < _network.size(); ++i)
    {
        weights.emplace_back();
        for (size_t j = 0; j < _network[i].size(); ++j)
        {
            weights[i - 1].emplace_back(_network[i][j].weights);
        }
    }
    return weights;
}

void MultiLayerPerceptronTrainee::printWeights()
{
    std::cout << std::endl;
    for (size_t i = 1; i < _network.size(); ++i)
    {
        for (int j = 0; j < _layers[i]; ++j)
        {
            std::cout << "Layer " << i + 1 << " Neuron " << j << ": ";
            for (auto &it : _network[i][j].weights)
            {
                std::cout << std::setw(10) << std::setprecision(5) << it << "  ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

std::vector<double> MultiLayerPerceptronTrainee::run(std::vector<double> x)
{
    _values[0] = x;
    for (size_t i = 1; i < _network.size(); ++i)
    {
        for (int j = 0; j < _layers[i]; ++j)
        {
            if (j == _layers[i] - 1 || !_droppedValues[i - 1][j])
            {
                _values[i][j] = _network[i][j].run(_values[i - 1]);
            }
        }
    }
    return _values.back();
}

// Run a single (x,y) pair with the backpropagation algorithm.
double MultiLayerPerceptronTrainee::bp(std::vector<double> x, std::vector<double> y)
{
    // Backpropagation steps
    // STEP 1: Feed a sample to the network
    std::vector<double> output = run(x);

    // STEP 2: Calculate the MSE
    std::vector<double> error;
    double MSE = 0.0;
    for (size_t i = 0; i < y.size(); ++i)
    {
        error.push_back(y[i] - output[i]);
        MSE += error[i] * error[i];
    }
    MSE /= _layers.back();

    // STEP 3: Calculate the output error terms
    for (size_t i = 0; i < output.size(); ++i)
    {
        _network_error.back()[i] = output[i] * (1 - output[i]) * (error[i]);
    }

    // STEP 4: Calculate the error term of each unit on each layer
    for (size_t i = _network.size() - 2; i > 0; --i)
    {
        for (size_t h = 0; h < _network[i].size(); ++h)
        {
            if (h == _layers[i] - 1 || !_droppedValues[i - 1][h])
            {
                double fwd_error = 0.0;
                for (int k = 0; k < _layers[i + 1]; ++k)
                {
                    fwd_error += _network[i + 1][k].weights[h] * _network_error[i + 1][k];
                }
                _network_error[i][h] = _values[i][h] * (1 - _values[i][h]) * fwd_error;
            }
        }
    }

    // STEP 5 & 6:
    for (size_t i = 1; i < _network.size(); ++i)
    {
        for (int j = 0; j < _layers[i]; ++j)
        {
            if (j == _layers[i] - 1 || !_droppedValues[i - 1][j])
            {
                for (int k = 0; k < _layers[i - 1]; ++k)
                {
                    _network[i][j].weights[k] += _learning_rate * _momentum * _network_error[i][j] * _values[i - 1][k];
                }
                _network[i][j].weights[_layers[i - 1]] += _learning_rate * _momentum * _network_error[i][j] * _bias;
            }
        }
    }
    return MSE;
}

void MultiLayerPerceptronTrainee::generateDropout()
{
    for (size_t i = 0; i < _droppedValues.size(); ++i)
    {
        for (size_t j = 0; j < _droppedValues[i].size(); ++j)
        {
            _droppedValues[i][j] = Random::randomPositiveDouble() < _dropout;
        }
    }
}

void MultiLayerPerceptronTrainee::disableDropout()
{
    for (size_t i = 0; i < _droppedValues.size(); ++i)
    {
        for (size_t j = 0; j < _droppedValues[i].size(); ++j)
        {
            _droppedValues[i][j] = false;
        }
    }
}