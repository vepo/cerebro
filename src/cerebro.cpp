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

using namespace std;

int main()
{
    srand(time(NULL));
    rand();

    cout << endl
         << endl
         << "------------- Logical Gate Example -------------"
         << endl
         << endl;
    Perceptron *p = new Perceptron(2);
    p->set_weights(OR_WEIGHTS);
    cout << "Gate: " << endl;
    cout << p->run({0, 0}) << endl;
    cout << p->run({0, 1}) << endl;
    cout << p->run({1, 0}) << endl;
    cout << p->run({1, 1}) << endl;

    cout << endl
         << endl
         << "------------- Hardcoded XOR Example -------------"
         << endl
         << endl;
    MultiLayerPerceptron mlp = MultiLayerPerceptron({2, 2, 1});
    mlp.set_weights({{NAND_WEIGHTS, OR_WEIGHTS}, {AND_WEIGHTS}});
    cout << "Hard-coded weights:\n";
    mlp.print_weights();

    cout << "XOR:" << endl;
    cout << " 0 0 = " << mlp.run({0, 0})[0] << endl;
    cout << " 0 1 = " << mlp.run({0, 1})[0] << endl;
    cout << " 1 0 = " << mlp.run({1, 0})[0] << endl;
    cout << " 1 1 = " << mlp.run({1, 1})[0] << endl;

    cout << endl
         << endl
         << "------------- Trained XOR Example -------------"
         << endl
         << endl;

    mlp = MultiLayerPerceptron({2, 2, 1});
    cout << "Training Neural Network as an XOR Gate..." << endl;
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
            cout << "MSE = " << MSE << endl;
        }
    }
    cout << endl
         << endl
         << "Trained weights (Compare to hard-coded weights):"
         << endl
         << endl;
    mlp.print_weights();

    cout << "XOR:" << endl;
    cout << " 0 0 = " << mlp.run({0, 0})[0] << endl;
    cout << " 0 1 = " << mlp.run({0, 1})[0] << endl;
    cout << " 1 0 = " << mlp.run({1, 0})[0] << endl;
    cout << " 1 1 = " << mlp.run({1, 1})[0] << endl;
    return 0;
}