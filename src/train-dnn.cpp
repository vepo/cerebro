#include <iostream>

#include "cmd/parameters.hpp"
#include "dataset/dataset.hpp"
#include "nn/multi-layer-perceptron-trainer.hpp"

int main(int argc, char *argv[])
{
    std::vector<std::string> args;
    if (argc > 1)
    {
        args.assign(argv + 1, argv + argc);
    }
    Parameters params = Parameters::parse(args);
    MultiLayerPerceptronTrainerParams mlpParams(Dataset(params.datasetFile()),
                                                params.inputNames(),
                                                params.outputNames(),
                                                params.layers());
    std::cout << "Training House Predictor..." << std::endl;
    return 0;
}