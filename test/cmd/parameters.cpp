#include "doctest.h"

#include "cmd/parameters.hpp"

TEST_CASE("Parameters")
{
    SUBCASE("Empty")
    {
        Parameters params = Parameters::parse({});
    }

    SUBCASE("Dataset")
    {
        Parameters params = Parameters::parse({"-d", "housing.csv",
                                               "-o", "housing.dts",
                                               "-in", "GEO,SIZE",
                                               "-out", "PRICE",
                                               "-l", "2,14,10,1"});
        CHECK_EQ(params.datasetFile(), "housing.csv");
        CHECK_EQ(params.outpuFile(), "housing.dts");
        CHECK_EQ(params.inputNames(), std::vector<std::string>({"GEO", "SIZE"}));
        CHECK_EQ(params.outputNames(), std::vector<std::string>({"PRICE"}));
        CHECK_EQ(params.layers(), std::vector<int>({2, 14, 10, 1}));
    }
}