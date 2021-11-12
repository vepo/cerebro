#pragma once
#include <algorithm>
#include <vector>
#include <iostream>
#include <random>
#include <numeric>
#include <cmath>
#include <time.h>
#include "perceptron.hpp"

using namespace std;

class MultiLayerPerceptron
{
public:
    MultiLayerPerceptron(vector<int> layers, double bias = 1.0, double eta = 0.5);
    void set_weights(vector<vector<vector<double>>> w_init);
    void print_weights();
    vector<double> run(vector<double> x);
    double bp(vector<double> x, vector<double> y);

    vector<int> layers;
    double bias;
    double eta;
    vector<vector<Perceptron>> network;
    vector<vector<double>> values;
    vector<vector<double>> d;
};