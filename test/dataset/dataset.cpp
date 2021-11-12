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
        CHECK_EQ(dataset.cols, 3);
        CHECK_EQ(dataset.rows, 3);
        CHECK_EQ(dataset.cell(0, 0), "1");
        CHECK_EQ(dataset.cell(0, 1), "Joe");
        CHECK_EQ(dataset.cell(0, 2), "38");
        CHECK_EQ(dataset.cell(1, 0), "2");
        CHECK_EQ(dataset.cell(1, 1), "Alice");
        CHECK_EQ(dataset.cell(1, 2), "24");
        CHECK_EQ(dataset.cell(2, 0), "3");
        CHECK_EQ(dataset.cell(2, 1), "Bob");
        CHECK_EQ(dataset.cell(2, 2), "75");

        CHECK_EQ(dataset.cell(1, "ID"), "2");
        CHECK_EQ(dataset.cell(1, "NAME"), "Alice");
        CHECK_EQ(dataset.cell(1, "AGE"), "24");
    }
}