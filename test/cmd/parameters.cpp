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
                                               "-l", "2,14,10,1",
                                               "-e", "3000"});
        REQUIRE_EQ(params.datasetFile(), "housing.csv");
        REQUIRE_EQ(params.outpuFile(), "housing.dts");
        REQUIRE_EQ(params.inputNames(), std::vector<std::string>({"GEO", "SIZE"}));
        REQUIRE_EQ(params.outputNames(), std::vector<std::string>({"PRICE"}));
        REQUIRE_EQ(params.layers(), std::vector<int>({2, 14, 10, 1}));
        REQUIRE_EQ(params.epochs(), 3000);
    }
}