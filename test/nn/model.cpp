#include "doctest.h"
#include "nn/model.hpp"

#include <string>
#include <vector>

TEST_CASE("model")
{
    SUBCASE("Save Model")
    {
        Model model("model",
                    std::vector<std::string>({"A", "B", "C"}),
                    std::vector<std::string>({"D", "E"}),
                    std::vector<std::vector<std::vector<double>>>({{{0.0, 0.1},
                                                                    {0.2, 0.3}},
                                                                   {{1.0, 1, 1}}}),
                    0.3);
        REQUIRE(model.save("./build/models/tc-001/model.mdl"));

        Model readModel = Model::load("./build/models/tc-001/model.mdl");
        REQUIRE_EQ(readModel.name(), "model");
        REQUIRE_EQ(readModel.inputs(), std::vector<std::string>({"A", "B", "C"}));
        REQUIRE_EQ(readModel.outputs(), std::vector<std::string>({"D", "E"}));
    }

    SUBCASE("Override Model")
    {
        Model model("model",
                    std::vector<std::string>({"A", "B", "C"}),
                    std::vector<std::string>({"D", "E"}),
                    std::vector<std::vector<std::vector<double>>>({{{0.0, 0.1},
                                                                    {0.2, 0.3}},
                                                                   {{1.0, 1, 1}}}),
                    0.3);
        REQUIRE(model.save("./build/models/tc-002/model.mdl"));

        Model readModel = Model::load("./build/models/tc-002/model.mdl");
        REQUIRE_EQ(readModel.name(), "model");
        REQUIRE_EQ(readModel.inputs(), std::vector<std::string>({"A", "B", "C"}));
        REQUIRE_EQ(readModel.outputs(), std::vector<std::string>({"D", "E"}));

        Model modelOverride("modelOverride",
                            std::vector<std::string>({"F", "G"}),
                            std::vector<std::string>({"H", "I", "J"}),
                            std::vector<std::vector<std::vector<double>>>({{{0.0, 0.1},
                                                                            {0.2, 0.3}},
                                                                           {{1.0, 1, 1}}}),
                            0.3);
        REQUIRE(modelOverride.save("./build/models/tc-002/model.mdl"));

        Model readModelOverride = Model::load("./build/models/tc-002/model.mdl");
        REQUIRE_EQ(readModelOverride.name(), "modelOverride");
        REQUIRE_EQ(readModelOverride.inputs(), std::vector<std::string>({"F", "G"}));
        REQUIRE_EQ(readModelOverride.outputs(), std::vector<std::string>({"H", "I", "J"}));
    }
}