#include "doctest.h"
#include <iostream>
#include "nn/multi-layer-perceptron-trainer.hpp"

TEST_CASE("MultiLayerPerceptron Trainer")
{

    Dataset ds("./data/forest-fires/forestfires.csv");
    MultiLayerPerceptronTrainerParams params(ds,
                                             std::vector<std::string>({"month", "FFMC", "DMC", "DC", "ISI", "temp", "RH", "wind", "rain"}),
                                             std::vector<std::string>({"area"}),
                                             std::vector<int>({9, 9, 3, 1}),
                                             5000);
    MultiLayerPerceptronTrainer trainer(params);
    Model model = trainer.train();
}