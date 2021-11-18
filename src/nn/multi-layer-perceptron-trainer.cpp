#include "nn/multi-layer-perceptron-trainer.hpp"
#include "nn/multi-layer-perceptron.hpp"
#include <iostream>

MultiLayerPerceptronTrainerParams::MultiLayerPerceptronTrainerParams(const Dataset &dataset,
                                                                     const std::vector<std::string> &xNames,
                                                                     const std::vector<std::string> &yNames,
                                                                     const std::vector<int> &layers,
                                                                     double testSize,
                                                                     double validationSize) : dataset(dataset),
                                                                                              xNames(xNames),
                                                                                              yNames(yNames),
                                                                                              layers(layers),
                                                                                              testSize(testSize),
                                                                                              validationSize(validationSize)
{
}

MultiLayerPerceptronTrainer::MultiLayerPerceptronTrainer(const MultiLayerPerceptronTrainerParams &params) : params(params)
{
}

void MultiLayerPerceptronTrainer::run()
{
    MultiLayerPerceptron mlp = MultiLayerPerceptron(this->params.layers);
    std::cout << "Training Neural Network..." << std::endl;
    //this->params->dataset->normalize();
    Pair<Dataset> pair = this->params.dataset.split(this->params.testSize);
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
            std::cout << "MSE = " << MSE << std::endl;
        }
    }
    std::cout << std::endl
              << std::endl
              << "Trained weights (Compare to hard-coded weights):"
              << std::endl
              << std::endl;
    mlp.print_weights();
}