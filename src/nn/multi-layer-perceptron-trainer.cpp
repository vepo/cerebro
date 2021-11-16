#include "nn/multi-layer-perceptron-trainer.hpp"
#include "nn/multi-layer-perceptron.hpp"
#include <iostream>

MultiLayerPerceptronTrainerParams::MultiLayerPerceptronTrainerParams(Dataset *dataset,
                                                                     vector<string> xNames,
                                                                     vector<string> yNames,
                                                                     vector<int> layers,
                                                                     double testSize,
                                                                     double validationSize)
{
    this->dataset = dataset;
    this->xNames = xNames;
    this->yNames = yNames;
    this->layers = layers;
    this->testSize = testSize;
    this->validationSize = validationSize;
}

MultiLayerPerceptronTrainer::MultiLayerPerceptronTrainer(MultiLayerPerceptronTrainerParams *params)
{
    this->params = params;
}

void MultiLayerPerceptronTrainer::run()
{
    MultiLayerPerceptron mlp = MultiLayerPerceptron(this->params->layers);
    cout << "Training Neural Network..." << endl;
    //this->params->dataset->normalize();
    this->params->dataset->split(this->params->testSize);
    double MSE;
    for (int i = 0; i < 3000; ++i)
    {
        MSE = 0.0;
        MSE += mlp.bp({0, 0}, {0});
        MSE += mlp.bp({0, 1}, {1});
        MSE += mlp.bp({1, 0}, {1});
        MSE += mlp.bp({1, 1}, {0});
        MSE = MSE / 4.0;
        if (i % 100 == 0)
        {
            cout << "MSE = " << MSE << endl;
        }
    }
    cout << endl
         << endl
         << "Trained weights (Compare to hard-coded weights):"
         << endl
         << endl;
    mlp.print_weights();
}