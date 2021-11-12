#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "dataset/dataset.hpp"

TEST_CASE("Reading dataset")
{
    SUBCASE("Simple CSV")
    {
        Dataset dataset = Dataset("./test/dataset/simple.csv");
        CHECK_EQ(dataset.path, "./test/dataset/simple.csv");
        CHECK_EQ(dataset.names, vector<string>({"ID", "NAME", "AGE"}));
    }
}