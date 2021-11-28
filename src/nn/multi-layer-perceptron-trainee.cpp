#include "nn/multi-layer-perceptron-trainee.hpp"
#include <iostream>
#include <iomanip>
#include "utils/random.hpp"

MultiLayerPerceptronTrainee::MultiLayerPerceptronTrainee(std::vector<int> layers,
                                                         double bias,
                                                         double learning_rate,
                                                         double momentum,
                                                         double dropout) : layers(layers),
                                                                           bias(bias),
                                                                           learning_rate(learning_rate),
                                                                           momentum(momentum),
                                                                           dropout(dropout)
{
    for (size_t i = 0; i < layers.size(); ++i)
    {
        values.emplace_back(std::vector<double>(layers[i], 0.0));
        network_error.emplace_back(std::vector<double>(layers[i], 0.0));
        network.emplace_back();
        droppedValues.emplace_back();
        if (i > 0)
        {
            droppedValues.emplace_back();
            for (int j = 0; j < layers[i]; ++j)
            {
                if (j != layers[i] - 1)
                {
                    droppedValues[i - 1].emplace_back(false);
                }
                network[i].emplace_back(Perceptron(layers[i - 1], bias));
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
            network[i + 1][j].setWeights(w_init[i][j]);
        }
    }
}

std::vector<std::vector<std::vector<double>>> MultiLayerPerceptronTrainee::get_weights()
{
    std::vector<std::vector<std::vector<double>>> weights;

    for (size_t i = 1; i < network.size(); ++i)
    {
        weights.emplace_back();
        for (size_t j = 0; j < network[i].size(); ++j)
        {
            weights[i - 1].emplace_back(network[i][j].weights);
        }
    }
    return weights;
}

void MultiLayerPerceptronTrainee::printWeights()
{
    std::cout << std::endl;
    for (size_t i = 1; i < network.size(); ++i)
    {
        for (int j = 0; j < layers[i]; ++j)
        {
            std::cout << "Layer " << i + 1 << " Neuron " << j << ": ";
            for (auto &it : network[i][j].weights)
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
    values[0] = x;
    for (size_t i = 1; i < network.size(); ++i)
    {
        for (int j = 0; j < layers[i]; ++j)
        {
            if (j == layers[i] - 1 || !droppedValues[i - 1][j])
            {
                values[i][j] = network[i][j].run(values[i - 1]);
            }
        }
    }
    return values.back();
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
    MSE /= layers.back();

    // STEP 3: Calculate the output error terms
    for (size_t i = 0; i < output.size(); ++i)
    {
        network_error.back()[i] = output[i] * (1 - output[i]) * (error[i]);
    }

    // STEP 4: Calculate the error term of each unit on each layer
    for (size_t i = network.size() - 2; i > 0; --i)
    {
        for (size_t h = 0; h < network[i].size(); ++h)
        {
            if (h == layers[i] - 1 || !droppedValues[i - 1][h])
            {
                double fwd_error = 0.0;
                for (int k = 0; k < layers[i + 1]; ++k)
                {
                    fwd_error += network[i + 1][k].weights[h] * network_error[i + 1][k];
                }
                network_error[i][h] = values[i][h] * (1 - values[i][h]) * fwd_error;
            }
        }
    }

    // STEP 5 & 6:
    for (size_t i = 1; i < network.size(); ++i)
    {
        for (int j = 0; j < layers[i]; ++j)
        {
            if (j == layers[i] - 1 || !droppedValues[i - 1][j])
            {
                for (int k = 0; k < layers[i - 1]; ++k)
                {
                    network[i][j].weights[k] += learning_rate * momentum * network_error[i][j] * values[i - 1][k];
                }
                network[i][j].weights[layers[i - 1]] += learning_rate * momentum * network_error[i][j] * bias;
            }
        }
    }
    return MSE;
}

void MultiLayerPerceptronTrainee::generateDropout()
{
    for (size_t i = 0; i < droppedValues.size(); ++i)
    {
        for (size_t j = 0; j < droppedValues[i].size(); ++j)
        {
            droppedValues[i][j] = Random::randomPositiveDouble() < dropout;
        }
    }
}

void MultiLayerPerceptronTrainee::disableDropout()
{
    for (size_t i = 0; i < droppedValues.size(); ++i)
    {
        for (size_t j = 0; j < droppedValues[i].size(); ++j)
        {
            droppedValues[i][j] = false;
        }
    }
}