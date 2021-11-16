#include "nn/multi-layer-perceptron.hpp"

MultiLayerPerceptron::MultiLayerPerceptron(std::vector<int> layers,
                                           double bias,
                                           double eta)
{
    this->layers = layers;
    this->bias = bias;
    this->eta = eta;

    for (size_t i = 0; i < layers.size(); ++i)
    {
        values.push_back(std::vector<double>(layers[i], 0.0));
        d.push_back(std::vector<double>(layers[i], 0.0));
        network.push_back(std::vector<Perceptron>());
        if (i > 0)
        {
            for (int j = 0; j < layers[i]; ++j)
            {
                network[i].push_back(Perceptron(layers[i - 1], bias));
            }
        }
    }
}

void MultiLayerPerceptron::set_weights(std::vector<std::vector<std::vector<double>>> w_init)
{
    for (size_t i = 0; i < w_init.size(); ++i)
    {
        for (size_t j = 0; j < w_init[i].size(); ++j)
        {
            network[i + 1][j].set_weights(w_init[i][j]);
        }
    }
}

void MultiLayerPerceptron::print_weights()
{
    std::cout << std::endl;
    for (size_t i = 1; i < network.size(); ++i)
    {
        for (int j = 0; j < layers[i]; ++j)
        {
            std::cout << "Layer " << i + 1 << " Neuron " << j << ": ";
            for (auto &it : network[i][j].weights)
            {
                std::cout << it << "\t";
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

std::vector<double> MultiLayerPerceptron::run(std::vector<double> x)
{
    values[0] = x;
    for (size_t i = 1; i < network.size(); ++i)
    {
        for (int j = 0; j < layers[i]; ++j)
        {
            values[i][j] = network[i][j].run(values[i - 1]);
        }
    }
    return values.back();
}

// Run a single (x,y) pair with the backpropagation algorithm.
double MultiLayerPerceptron::bp(std::vector<double> x, std::vector<double> y)
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
        d.back()[i] = output[i] * (1 - output[i]) * (error[i]);
    }

    // STEP 4: Calculate the error term of each unit on each layer
    for (size_t i = network.size() - 2; i > 0; --i)
    {
        for (size_t h = 0; h < network[i].size(); ++h)
        {
            double fwd_error = 0.0;
            for (int k = 0; k < layers[i + 1]; ++k)
            {
                fwd_error += network[i + 1][k].weights[h] * d[i + 1][k];
            }
            d[i][h] = values[i][h] * (1 - values[i][h]) * fwd_error;
        }
    }

    // STEP 5 & 6:
    for (size_t i = 1; i < network.size(); ++i)
    {
        for (int j = 0; j < layers[i]; ++j)
        {
            for (int k = 0; k < layers[i - 1] + 1; ++k)
            {
                double delta;
                if (k == layers[i - 1])
                {
                    delta = eta * d[i][j] * bias;
                }
                else
                {
                    delta = eta * d[i][j] * values[i - 1][k];
                }
                network[i][j].weights[k] += delta;
            }
        }
    }
    return MSE;
}