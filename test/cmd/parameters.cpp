#include "doctest.h"

#include "cmd/parameters.hpp"

TEST_CASE("Parameters")
{
    SUBCASE("Empty")
    {
        Parameters::parse({}, {});
    }

    SUBCASE("Dataset")
    {
        TrainerParameters params;
        std::vector<ParamOption> options{
            {.longOpt = "--dataset",
             .shortOpt = "-d",
             .type = OptionType::STRING,
             .dest = &params.datasetFile},
            {.longOpt = "--output-file",
             .shortOpt = "-o",
             .type = OptionType::STRING,
             .dest = &params.outpuFile},
            {.longOpt = "--input",
             .shortOpt = "-in",
             .type = OptionType::STRING_LIST,
             .dest = &params.inputNames},
            {.longOpt = "--output",
             .shortOpt = "-out",
             .type = OptionType::STRING_LIST,
             .dest = &params.outputNames},
            {.longOpt = "--layers",
             .shortOpt = "-l",
             .type = OptionType::INTEGER_LIST,
             .dest = &params.layers},
            {.longOpt = "--epochs",
             .shortOpt = "-e",
             .type = OptionType::INTEGER,
             .dest = &params.epochs}};

        Parameters::parse({"-d", "housing.csv",
                           "-o", "housing.dts",
                           "-in", "GEO,SIZE",
                           "-out", "PRICE",
                           "-l", "2,14,10,1",
                           "-e", "3000"},
                          options);
        REQUIRE_EQ(params.datasetFile, "housing.csv");
        REQUIRE_EQ(params.outpuFile, "housing.dts");
        REQUIRE_EQ(params.inputNames, std::vector<std::string>({"GEO", "SIZE"}));
        REQUIRE_EQ(params.outputNames, std::vector<std::string>({"PRICE"}));
        REQUIRE_EQ(params.layers, std::vector<int>({2, 14, 10, 1}));
        REQUIRE_EQ(params.epochs, 3000);
    }
}