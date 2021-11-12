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

    return 0;
}