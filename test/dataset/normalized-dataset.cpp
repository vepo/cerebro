#include "doctest.h"

#include "dataset/dataset.hpp"

TEST_CASE("Reading dataset")
{
    Dataset dataset = Dataset("./test/dataset/simple.csv");
    NormalizedDataset nd = dataset.normalize();
    CHECK_EQ(nd.cell(0, 0), 0.0);
}