#pragma once
#include "dataset/dataset.hpp"

class MultiLayerPerceptronTrainerParams
{
public:
    MultiLayerPerceptronTrainerParams(Dataset *dataset,
                                      vector<string> xNames,
                                      vector<string> yNames,
                                      vector<int> layers,
                                      double testSize = 0.15,
                                      double validationSize = 0.15);
    Dataset *dataset;
    vector<string> xNames;
    vector<string> yNames;
    vector<int> layers;
    double testSize;
    double validationSize;
};

class MultiLayerPerceptronTrainer
{
public:
    MultiLayerPerceptronTrainer(MultiLayerPerceptronTrainerParams *params);
    void run();

private:
    MultiLayerPerceptronTrainerParams *params;
};