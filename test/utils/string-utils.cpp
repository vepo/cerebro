#include "doctest.h"

#include "utils/string-utils.hpp"

TEST_CASE("Removing Whitespace")
{
    REQUIRE_EQ("ABC", StringUtils::trim("ABC\r"));
    REQUIRE_EQ("ABC", StringUtils::trim("\rABC"));
    REQUIRE_EQ("ABC", StringUtils::trim(" ABC"));
    REQUIRE_EQ("ABC", StringUtils::trim("ABC "));
    REQUIRE_EQ("ABC", StringUtils::trim("\tABC"));
    REQUIRE_EQ("ABC", StringUtils::trim("ABC\t"));
    REQUIRE_EQ("ABC", StringUtils::trim("\t\t ABC\t \t\r"));
}