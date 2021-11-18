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

#include "doctest.h"

#include "nn/perceptron.hpp"
TEST_CASE("Perceptron")
{
    SUBCASE("AND")
    {
        Perceptron andPerceptron(2);
        andPerceptron.set_weights(AND_WEIGHTS);
        CHECK_EQ(doctest::Approx(andPerceptron.run({0, 0})).epsilon(0.1), 0.0);
        CHECK_EQ(doctest::Approx(andPerceptron.run({0, 1})).epsilon(0.1), 0.0);
        CHECK_EQ(doctest::Approx(andPerceptron.run({1, 0})).epsilon(0.1), 0.0);
        CHECK_EQ(doctest::Approx(andPerceptron.run({1, 1})).epsilon(0.1), 1.0);
    }

    SUBCASE("OR")
    {
        Perceptron andPerceptron(2);
        andPerceptron.set_weights(OR_WEIGHTS);
        CHECK_EQ(doctest::Approx(andPerceptron.run({0, 0})).epsilon(0.1), 0.0);
        CHECK_EQ(doctest::Approx(andPerceptron.run({0, 1})).epsilon(0.1), 1.0);
        CHECK_EQ(doctest::Approx(andPerceptron.run({1, 0})).epsilon(0.1), 1.0);
        CHECK_EQ(doctest::Approx(andPerceptron.run({1, 1})).epsilon(0.1), 1.0);
    }

    SUBCASE("NAND")
    {
        Perceptron andPerceptron(2);
        andPerceptron.set_weights(NAND_WEIGHTS);
        CHECK_EQ(doctest::Approx(andPerceptron.run({0, 0})).epsilon(0.1), 1.0);
        CHECK_EQ(doctest::Approx(andPerceptron.run({0, 1})).epsilon(0.1), 1.0);
        CHECK_EQ(doctest::Approx(andPerceptron.run({1, 0})).epsilon(0.1), 1.0);
        CHECK_EQ(doctest::Approx(andPerceptron.run({1, 1})).epsilon(0.1), 0.0);
    }
}