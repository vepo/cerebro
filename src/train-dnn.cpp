#include <iostream>

#include "cmd/parameters.hpp"
#include "dataset/dataset.hpp"
#include "nn/multi-layer-perceptron-trainer.hpp"

int main(int argc, char *argv[])
{
    Parameters params = Parameters::parse(argc, argv);
    MultiLayerPerceptronTrainerParams params(params.datasetFile(),
                                             params.inputNames(),
                                             params.outpuFile(),
                                             params.layers());
    std::cout << "Training House Predictor..." << std::endl;
    return 0;
}