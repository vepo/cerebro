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
        CHECK(reader.endOfLine());

        CHECK_EQ(reader.nextToken(), "1");
        CHECK(reader.hasNextToken());
        CHECK_FALSE(reader.endOfLine());
        CHECK_EQ(reader.nextToken(), "Joe");
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