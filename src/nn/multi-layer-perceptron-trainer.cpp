#include "nn/multi-layer-perceptron-trainer.hpp"

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