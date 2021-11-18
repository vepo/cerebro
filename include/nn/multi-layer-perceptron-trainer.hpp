#pragma once
#include "dataset/dataset.hpp"

class MultiLayerPerceptronTrainerParams
{
public:
    MultiLayerPerceptronTrainerParams(const Dataset &dataset,
                                      const std::vector<std::string> &xNames,
                                      const std::vector<std::string> &yNames,
                                      const std::vector<int> &layers,
                                      double testSize = 0.15,
                                      double validationSize = 0.15);
    const Dataset &dataset;
    const std::vector<std::string> &xNames;
    const std::vector<std::string> &yNames;
    const std::vector<int> &layers;
    double testSize;
    double validationSize;
};

class MultiLayerPerceptronTrainer
{
public:
    explicit MultiLayerPerceptronTrainer(const MultiLayerPerceptronTrainerParams &params);
    void run();

private:
    const MultiLayerPerceptronTrainerParams &params;
};