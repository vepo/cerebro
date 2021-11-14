#include "doctest.h"

#include "utils/string-utils.hpp"

TEST_CASE("Removing Whitespace")
{
    CHECK_EQ("ABC", StringUtils::trim("ABC\r"));
    CHECK_EQ("ABC", StringUtils::trim("\rABC"));
    CHECK_EQ("ABC", StringUtils::trim(" ABC"));
    CHECK_EQ("ABC", StringUtils::trim("ABC "));
    CHECK_EQ("ABC", StringUtils::trim("\tABC"));
    CHECK_EQ("ABC", StringUtils::trim("ABC\t"));
    CHECK_EQ("ABC", StringUtils::trim("\t\t ABC\t \t\r"));
}