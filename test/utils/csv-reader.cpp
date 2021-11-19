#include "doctest.h"

#include "utils/csv-reader.hpp"
#include <regex>

TEST_CASE("Reading CSV")
{
    SUBCASE("REGEX")
    {
        CHECK(regex_match("ABC,", CSVReader::cellRegex));
        CHECK(regex_match("ABC\n", CSVReader::cellRegex));
        CHECK(regex_match("ABC\r\n", CSVReader::cellRegex));
        CHECK(regex_match("ABC\t\r\n", CSVReader::cellRegex));
        CHECK(regex_match("ABC,DEF,GHE\n", CSVReader::lineRegex));
        CHECK(regex_match("\"ABC\",DEF,GHE\n", CSVReader::lineRegex));
        CHECK(regex_match("\"ABC \",DEF,GHE\n", CSVReader::lineRegex));

        CHECK(regex_match("\"A\"\"BC\"\"\",", CSVReader::cellRegex));

        CHECK(regex_match("\"ABC\",DEF,GHE\n", CSVReader::lineEscapedRegex));
        CHECK(regex_match("\"\"\"ABC\"\"\",DEF,GHE\n", CSVReader::lineEscapedRegex));
    }

    SUBCASE("Simple")
    {
        CSVReader reader = CSVReader("./test/dataset/simple.csv");
        CHECK(reader.hasNextToken());
        CHECK_EQ(reader.nextToken(), "ID");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "NAME");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "AGE");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "SEX");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "CLASS");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "GRADE");
        CHECK(reader.hasNextToken());
        CHECK(reader.endOfLine());

        CHECK_EQ(reader.nextToken(), "1");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "Joe");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "38");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "M");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "C");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "10");
        CHECK(reader.hasNextToken());
        CHECK(reader.endOfLine());

        CHECK_EQ(reader.nextToken(), "2");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "Alice");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "24");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "F");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "A");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "7.5");
        CHECK(reader.hasNextToken());
        CHECK(reader.endOfLine());

        CHECK_EQ(reader.nextToken(), "3");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "Bob");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "75");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "M");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "B");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "5");
        CHECK(reader.hasNextToken());
        CHECK(reader.endOfLine());

        CHECK_EQ(reader.nextToken(), "4");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "Carol");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "32");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "F");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "A");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "2");
        CHECK(reader.hasNextToken());
        CHECK(reader.endOfLine());

        CHECK_EQ(reader.nextToken(), "5");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "Dan");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "14");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "M");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "B");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "6.6");
        CHECK(reader.hasNextToken());
        CHECK(reader.endOfLine());

        CHECK_EQ(reader.nextToken(), "6");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "Erin");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "76");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "M");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "C");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "9.1");
        CHECK_FALSE(reader.hasNextToken());
        CHECK(reader.endOfLine());
    }

    SUBCASE("Escaped")
    {
        CSVReader reader = CSVReader("./test/dataset/escaped.csv");
        CHECK(reader.hasNextToken());
        CHECK_EQ(reader.nextToken(), "ID");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "NAME");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "AGE");
        CHECK(reader.hasNextToken());
        CHECK(reader.endOfLine());

        CHECK_EQ(reader.nextToken(), "1");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "Doe, Joe");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "38");
        CHECK(reader.hasNextToken());
        CHECK(reader.endOfLine());

        CHECK_EQ(reader.nextToken(), "2");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "Alice");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "24");
        CHECK(reader.hasNextToken());
        CHECK(reader.endOfLine());

        CHECK_EQ(reader.nextToken(), "3");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "Bob");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "75");
        CHECK_FALSE(reader.hasNextToken());
        CHECK(reader.endOfLine());
    }

    SUBCASE("Escaped CRLF")
    {
        CSVReader reader = CSVReader("./test/dataset/escaped-crlf.csv");
        CHECK(reader.hasNextToken());
        CHECK_EQ(reader.nextToken(), "ID");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "NAME");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "AGE");
        CHECK(reader.hasNextToken());
        CHECK(reader.endOfLine());

        CHECK_EQ(reader.nextToken(), "1");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "Doe\r\nJoe");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "38");
        CHECK(reader.hasNextToken());
        CHECK(reader.endOfLine());

        CHECK_EQ(reader.nextToken(), "2");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "Alice");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "24");
        CHECK(reader.hasNextToken());
        CHECK(reader.endOfLine());

        CHECK_EQ(reader.nextToken(), "3");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "Bob");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "75");
        CHECK_FALSE(reader.hasNextToken());
        CHECK(reader.endOfLine());
    }

    SUBCASE("Escaped with quotes")
    {
        CSVReader reader = CSVReader("./test/dataset/escaped-with-quotes.csv");
        CHECK(reader.hasNextToken());
        CHECK_EQ(reader.nextToken(), "ID");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "NAME");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "AGE");
        CHECK(reader.hasNextToken());
        CHECK(reader.endOfLine());

        CHECK_EQ(reader.nextToken(), "1");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "Doe \"Joe\"");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "38");
        CHECK(reader.hasNextToken());
        CHECK(reader.endOfLine());

        CHECK_EQ(reader.nextToken(), "2");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "Alice");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "24");
        CHECK(reader.hasNextToken());
        CHECK(reader.endOfLine());

        CHECK_EQ(reader.nextToken(), "3");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "Bob");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "75");
        CHECK_FALSE(reader.hasNextToken());
        CHECK(reader.endOfLine());
    }
}

#include <iostream>

TEST_CASE("Load big CSV")
{
    CSVReader reader("./data/forest-fires/forestfires.csv");

    for (int row = 0; row < 518; ++row)
    {
        for (int col = 0; col < 12; ++col)
        {
            REQUIRE_MESSAGE(reader.hasNextToken(), "Check hasNextToken (", row, ",", col, ")");
            std::string token = reader.nextToken();
            REQUIRE_MESSAGE(token.size() > 0, "Check token (", row, ",", col, "): ", token);
            REQUIRE_FALSE_MESSAGE(reader.endOfLine(), "CHECK endOfLine (", row, ",", col, ")");
        }
        std::string token = reader.nextToken();
        REQUIRE_MESSAGE(token.size() > 0, "Check token (", row, ",", 13, "): ", token);
        if (row == 517)
        {
            REQUIRE_FALSE_MESSAGE(reader.hasNextToken(), "Check hasNextToken (", row, ",", 13, ")");
        }
        else
        {
            REQUIRE_MESSAGE(reader.hasNextToken(), "Check hasNextToken (", row, ",", 13, ")");
        }
        REQUIRE_MESSAGE(reader.endOfLine(), "CHECK endOfLine (", row, ",", 13, ")");
    }
}