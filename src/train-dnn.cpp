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

    TrainerParameters params;
    std::vector<ParamOption> options{
        {.longOpt = "--dataset",
         .shortOpt = "-d",
         .type = OptionType::STRING,
         .dest = &params.datasetFile},
        {.longOpt = "--output-file",
         .shortOpt = "-o",
         .type = OptionType::STRING,
         .dest = &params.outpuFile},
        {.longOpt = "--input",
         .shortOpt = "-in",
         .type = OptionType::STRING_LIST,
         .dest = &params.inputNames},
        {.longOpt = "--output",
         .shortOpt = "-out",
         .type = OptionType::STRING_LIST,
         .dest = &params.outputNames},
        {.longOpt = "--layers",
         .shortOpt = "-l",
         .type = OptionType::INTEGER_LIST,
         .dest = &params.layers},
        {.longOpt = "--epochs",
         .shortOpt = "-e",
         .type = OptionType::INTEGER,
         .dest = &params.epochs}};

    Parameters::parse(args, options);
    MultiLayerPerceptronTrainerParams mlpParams(Dataset(params.datasetFile),
                                                params.inputNames,
                                                params.outputNames,
                                                params.layers);
    std::cout << "Training House Predictor..." << std::endl;
    return 0;
}