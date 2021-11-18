#include "doctest.h"

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

#include "nn/multi-layer-perceptron.hpp"
#include <iostream>

TEST_CASE("MultiLayerPerceptron")
{
    SUBCASE("Loaded values")
    {
        MultiLayerPerceptron xorPerceptron({2, 2, 1});
        xorPerceptron.set_weights({{NAND_WEIGHTS, OR_WEIGHTS}, {AND_WEIGHTS}});

        CHECK_EQ(doctest::Approx(xorPerceptron.run({0, 0})[0]).epsilon(0.1), 0.0);
        CHECK_EQ(doctest::Approx(xorPerceptron.run({0, 1})[0]).epsilon(0.1), 1.0);
        CHECK_EQ(doctest::Approx(xorPerceptron.run({1, 0})[0]).epsilon(0.1), 1.0);
        CHECK_EQ(doctest::Approx(xorPerceptron.run({1, 1})[0]).epsilon(0.1), 0.0);
    }

    SUBCASE("Trained values")
    {
        MultiLayerPerceptron xorPerceptron({2, 2, 1}, 1.0, 0.5, 0.6);
        double MSE;
        for (int i = 0; i < 3000; ++i)
        {
            MSE = 0.0;
            MSE += xorPerceptron.bp({0, 0}, {0});
            MSE += xorPerceptron.bp({0, 1}, {1});
            MSE += xorPerceptron.bp({1, 0}, {1});
            MSE += xorPerceptron.bp({1, 1}, {0});
            MSE = MSE / 4.0;
        }

        CHECK_EQ(doctest::Approx(MSE).epsilon(0.3), 0.0);
        CHECK_EQ(doctest::Approx(xorPerceptron.run({0, 0})[0]).epsilon(0.4), 0.0);
        CHECK_EQ(doctest::Approx(xorPerceptron.run({0, 1})[0]).epsilon(0.4), 1.0);
        CHECK_EQ(doctest::Approx(xorPerceptron.run({1, 0})[0]).epsilon(0.4), 1.0);
        CHECK_EQ(doctest::Approx(xorPerceptron.run({1, 1})[0]).epsilon(0.4), 0.0);

        xorPerceptron.print_weights();
    }
}