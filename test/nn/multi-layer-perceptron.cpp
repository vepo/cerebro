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

TEST_CASE("MultiLayerPerceptron")
{
    SUBCASE("Loaded values")
    {
        MultiLayerPerceptron xorPerceptron({{NAND_WEIGHTS, OR_WEIGHTS}, {AND_WEIGHTS}});

        REQUIRE_EQ(doctest::Approx(xorPerceptron.run({0, 0})[0]).epsilon(0.1), 0.0);
        REQUIRE_EQ(doctest::Approx(xorPerceptron.run({0, 1})[0]).epsilon(0.1), 1.0);
        REQUIRE_EQ(doctest::Approx(xorPerceptron.run({1, 0})[0]).epsilon(0.1), 1.0);
        REQUIRE_EQ(doctest::Approx(xorPerceptron.run({1, 1})[0]).epsilon(0.1), 0.0);
    }
}