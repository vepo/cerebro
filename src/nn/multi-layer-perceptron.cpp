#include "nn/multi-layer-perceptron.hpp"

MultiLayerPerceptron::MultiLayerPerceptron(vector<int> layers, double bias, double eta)
{
    this->layers = layers;
    this->bias = bias;
    this->eta = eta;

    for (size_t i = 0; i < layers.size(); ++i)
    {
        values.push_back(vector<double>(layers[i], 0.0));
        network.push_back(vector<Perceptron>());
        if (i > 0)
        {
            for (int j = 0; j < layers[i]; ++j)
            {
                network[i].push_back(Perceptron(layers[i - 1], bias));
            }
        }
    }
}

void MultiLayerPerceptron::set_weights(vector<vector<vector<double>>> w_init)
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
    cout << endl;
    for (size_t i = 1; i < network.size(); ++i)
    {
        for (int j = 0; j < layers[i]; ++j)
        {
            cout << "Layer " << i + 1 << " Neuron " << j << ": ";
            for (auto &it : network[i][j].weights)
            {
                cout << it << "\t";
            }
            cout << endl;
        }
    }
    cout << endl;
}

vector<double> MultiLayerPerceptron::run(vector<double> x)
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