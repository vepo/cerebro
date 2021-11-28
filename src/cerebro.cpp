#include <iostream>
#include "nn/perceptron.hpp"
#include "nn/multi-layer-perceptron.hpp"

#define AND_WEIGHTS \
    {               \
        10, 10, -15 \
    }
#define OR_WEIGHTS  \
    {               \
        15, 15, -10 \
    }
#define NAND_WEIGHTS \
    {                \
        -10, -10, 15 \
    }

int main()
{
    std::cout << std::endl
              << std::endl
              << "------------- Logical Gate Example -------------"
              << std::endl
              << std::endl;
    Perceptron *p = new Perceptron(2);
    p->setWeights(OR_WEIGHTS);
    std::cout << "Gate: " << std::endl;
    std::cout << p->run({0, 0}) << std::endl;
    std::cout << p->run({0, 1}) << std::endl;
    std::cout << p->run({1, 0}) << std::endl;
    std::cout << p->run({1, 1}) << std::endl;

    std::cout << std::endl
              << std::endl
              << "------------- Hardcoded XOR Example -------------"
              << std::endl
              << std::endl;
    MultiLayerPerceptron mlp = MultiLayerPerceptron({2, 2, 1});
    mlp.setWeights({{NAND_WEIGHTS, OR_WEIGHTS}, {AND_WEIGHTS}});
    std::cout << "Hard-coded weights:\n";
    mlp.printWeights();

    std::cout << "XOR:" << std::endl;
    std::cout << " 0 0 = " << mlp.run({0, 0})[0] << std::endl;
    std::cout << " 0 1 = " << mlp.run({0, 1})[0] << std::endl;
    std::cout << " 1 0 = " << mlp.run({1, 0})[0] << std::endl;
    std::cout << " 1 1 = " << mlp.run({1, 1})[0] << std::endl;

    std::cout << std::endl
              << std::endl
              << "------------- Trained XOR Example -------------"
              << std::endl
              << std::endl;

    mlp = MultiLayerPerceptron({2, 2, 1});
    std::cout << "Training Neural Network as an XOR Gate..." << std::endl;
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
    mlp.printWeights();

    std::cout << "XOR:" << std::endl;
    std::cout << " 0 0 = " << mlp.run({0, 0})[0] << std::endl;
    std::cout << " 0 1 = " << mlp.run({0, 1})[0] << std::endl;
    std::cout << " 1 0 = " << mlp.run({1, 0})[0] << std::endl;
    std::cout << " 1 1 = " << mlp.run({1, 1})[0] << std::endl;
    return 0;
}