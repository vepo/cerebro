#pragma once
#include "dataset/dataset.hpp"

class MultiLayerPerceptronTrainerParams
{
public:
    MultiLayerPerceptronTrainerParams(const Dataset &dataset,
                                      std::vector<std::string> xNames,
                                      std::vector<std::string> yNames,
                                      std::vector<int> layers,
                                      int epochs = 3000,
                                      double testSize = 0.15,
                                      double validationSize = 0.20);
    const Dataset &dataset;
    std::vector<std::string> xNames;
    std::vector<std::string> yNames;
    std::vector<int> layers;
    int epochs;
    double testSize;
    double validationSize;
};

class MultiLayerPerceptronTrainer
{
public:
    explicit MultiLayerPerceptronTrainer(const MultiLayerPerceptronTrainerParams &params);
    void train();

private:
    const MultiLayerPerceptronTrainerParams &params;
};