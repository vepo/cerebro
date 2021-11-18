#pragma once
#include "dataset/dataset.hpp"

class MultiLayerPerceptronTrainerParams
{
public:
    MultiLayerPerceptronTrainerParams(Dataset *dataset,
                                      std::vector<std::string> xNames,
                                      std::vector<std::string> yNames,
                                      std::vector<int> layers,
                                      double testSize = 0.15,
                                      double validationSize = 0.15);
    Dataset *dataset;
    std::vector<std::string> xNames;
    std::vector<std::string> yNames;
    std::vector<int> layers;
    double testSize;
    double validationSize;
};

class MultiLayerPerceptronTrainer
{
public:
    explicit MultiLayerPerceptronTrainer(MultiLayerPerceptronTrainerParams *params);
    void run();

private:
    MultiLayerPerceptronTrainerParams *params;
};