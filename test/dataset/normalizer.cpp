#include "doctest.h"

#include "dataset/normalizer.hpp"

TEST_CASE("Normalizer")
{
    NormalizeRule rule = Normalizer::inferRule({"1", "-100", "100", "500"});
    REQUIRE_EQ(rule.type, DataType::INTEGER);
    REQUIRE_EQ(doctest::Approx(rule.min).epsilon(0.01), -100);
    REQUIRE_EQ(doctest::Approx(rule.max).epsilon(0.01), 500);

    rule = Normalizer::inferRule({"1", "-100", "100", "500.0"});
    REQUIRE_EQ(rule.type, DataType::FLOATING_POINT);
    REQUIRE_EQ(doctest::Approx(rule.min).epsilon(0.01), -100);
    REQUIRE_EQ(doctest::Approx(rule.max).epsilon(0.01), 500);

    rule = Normalizer::inferRule({"A", "B", "C", "C", "B", "A", "C", "A"});
    REQUIRE_EQ(rule.type, DataType::ENUM);
    REQUIRE_EQ(rule.values, std::vector<std::string>({"A", "B", "C"}));

    rule = Normalizer::inferRule({"C", "B", "A", "B", "C", "C", "B", "A", "C", "A"});
    REQUIRE_EQ(rule.type, DataType::ENUM);
    REQUIRE_EQ(rule.values, std::vector<std::string>({"A", "B", "C"}));

    rule = Normalizer::inferRule({"MALE", "FEMALE", "MALE", "FEMALE", "MALE", "MALE", "MALE", "FEMALE"});
    REQUIRE_EQ(rule.type, DataType::BOOLEAN);
    REQUIRE_EQ(rule.values, std::vector<std::string>({"FEMALE", "MALE"}));

    DataType type = Normalizer::inferType({"MALE", "FEMALE", "MALE", "FEMALE", "MALE", "MALE", "MALE", "FEMALE"});
    REQUIRE_EQ(type, DataType::BOOLEAN);

    std::set<std::string> values;
    type = Normalizer::inferType({"MALE", "FEMALE", "MALE", "FEMALE", "MALE", "MALE", "MALE", "FEMALE"}, &values);
    REQUIRE_EQ(type, DataType::BOOLEAN);
    REQUIRE_EQ(values, std::set<std::string>({"FEMALE", "MALE"}));
}
