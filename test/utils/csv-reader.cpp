#include "doctest.h"

#include "utils/csv-reader.hpp"
#include <regex>

TEST_CASE("Reading CSV")
{
    SUBCASE("REGEX")
    {
        REQUIRE(regex_match("ABC,", CSVReader::cellRegex));
        REQUIRE(regex_match("ABC\n", CSVReader::cellRegex));
        REQUIRE(regex_match("ABC\r\n", CSVReader::cellRegex));
        REQUIRE(regex_match("ABC\t\r\n", CSVReader::cellRegex));
        REQUIRE(regex_match("ABC,DEF,GHE\n", CSVReader::lineRegex));
        REQUIRE(regex_match("\"ABC\",DEF,GHE\n", CSVReader::lineRegex));
        REQUIRE(regex_match("\"ABC \",DEF,GHE\n", CSVReader::lineRegex));

        REQUIRE(regex_match("\"A\"\"BC\"\"\",", CSVReader::cellRegex));

        REQUIRE(regex_match("\"ABC\",DEF,GHE\n", CSVReader::lineEscapedRegex));
        REQUIRE(regex_match("\"\"\"ABC\"\"\",DEF,GHE\n", CSVReader::lineEscapedRegex));
    }

    SUBCASE("Simple")
    {
        CSVReader reader = CSVReader("./test/dataset/simple.csv");
        REQUIRE(reader.hasNextToken());
        REQUIRE_EQ(reader.nextToken(), "ID");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "NAME");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "AGE");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "SEX");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "CLASS");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "GRADE");
        REQUIRE(reader.hasNextToken());
        REQUIRE(reader.endOfLine());

        REQUIRE_EQ(reader.nextToken(), "1");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "Joe");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "38");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "M");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "C");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "10");
        REQUIRE(reader.hasNextToken());
        REQUIRE(reader.endOfLine());

        REQUIRE_EQ(reader.nextToken(), "2");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "Alice");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "24");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "F");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "A");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "7.5");
        REQUIRE(reader.hasNextToken());
        REQUIRE(reader.endOfLine());

        REQUIRE_EQ(reader.nextToken(), "3");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "Bob");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "75");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "M");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "B");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "5");
        REQUIRE(reader.hasNextToken());
        REQUIRE(reader.endOfLine());

        REQUIRE_EQ(reader.nextToken(), "4");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "Carol");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "32");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "F");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "A");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "2");
        REQUIRE(reader.hasNextToken());
        REQUIRE(reader.endOfLine());

        REQUIRE_EQ(reader.nextToken(), "5");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "Dan");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "14");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "M");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "B");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "6.6");
        REQUIRE(reader.hasNextToken());
        REQUIRE(reader.endOfLine());

        REQUIRE_EQ(reader.nextToken(), "6");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "Erin");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "76");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "M");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "C");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "9.1");
        REQUIRE_FALSE(reader.hasNextToken());
        REQUIRE(reader.endOfLine());
    }

    SUBCASE("Escaped")
    {
        CSVReader reader = CSVReader("./test/dataset/escaped.csv");
        REQUIRE(reader.hasNextToken());
        REQUIRE_EQ(reader.nextToken(), "ID");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "NAME");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "AGE");
        REQUIRE(reader.hasNextToken());
        REQUIRE(reader.endOfLine());

        REQUIRE_EQ(reader.nextToken(), "1");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "Doe, Joe");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "38");
        REQUIRE(reader.hasNextToken());
        REQUIRE(reader.endOfLine());

        REQUIRE_EQ(reader.nextToken(), "2");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "Alice");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "24");
        REQUIRE(reader.hasNextToken());
        REQUIRE(reader.endOfLine());

        REQUIRE_EQ(reader.nextToken(), "3");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "Bob");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "75");
        REQUIRE_FALSE(reader.hasNextToken());
        REQUIRE(reader.endOfLine());
    }

    SUBCASE("Escaped CRLF")
    {
        CSVReader reader = CSVReader("./test/dataset/escaped-crlf.csv");
        REQUIRE(reader.hasNextToken());
        REQUIRE_EQ(reader.nextToken(), "ID");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "NAME");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "AGE");
        REQUIRE(reader.hasNextToken());
        REQUIRE(reader.endOfLine());

        REQUIRE_EQ(reader.nextToken(), "1");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "Doe\r\nJoe");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "38");
        REQUIRE(reader.hasNextToken());
        REQUIRE(reader.endOfLine());

        REQUIRE_EQ(reader.nextToken(), "2");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "Alice");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "24");
        REQUIRE(reader.hasNextToken());
        REQUIRE(reader.endOfLine());

        REQUIRE_EQ(reader.nextToken(), "3");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "Bob");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "75");
        REQUIRE_FALSE(reader.hasNextToken());
        REQUIRE(reader.endOfLine());
    }

    SUBCASE("Escaped with quotes")
    {
        CSVReader reader = CSVReader("./test/dataset/escaped-with-quotes.csv");
        REQUIRE(reader.hasNextToken());
        REQUIRE_EQ(reader.nextToken(), "ID");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "NAME");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "AGE");
        REQUIRE(reader.hasNextToken());
        REQUIRE(reader.endOfLine());

        REQUIRE_EQ(reader.nextToken(), "1");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "Doe \"Joe\"");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "38");
        REQUIRE(reader.hasNextToken());
        REQUIRE(reader.endOfLine());

        REQUIRE_EQ(reader.nextToken(), "2");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "Alice");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "24");
        REQUIRE(reader.hasNextToken());
        REQUIRE(reader.endOfLine());

        REQUIRE_EQ(reader.nextToken(), "3");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "Bob");
        REQUIRE(reader.hasNextToken());
        REQUIRE_FALSE(reader.endOfLine());
        REQUIRE_EQ(reader.nextToken(), "75");
        REQUIRE_FALSE(reader.hasNextToken());
        REQUIRE(reader.endOfLine());
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