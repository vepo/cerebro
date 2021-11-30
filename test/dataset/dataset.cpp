#include "doctest.h"

#include "dataset/dataset.hpp"

TEST_CASE("Reading dataset")
{
    SUBCASE("Simple CSV")
    {
        Dataset dataset("./test/dataset/simple.csv");
        REQUIRE_EQ(dataset.names(), std::vector<std::string>({"ID", "NAME", "AGE", "SEX", "CLASS", "GRADE"}));
        REQUIRE_EQ(dataset.cols(), 6);
        REQUIRE_EQ(dataset.rows(), 6);
        REQUIRE_EQ(dataset.cell(0, 0), "1");
        REQUIRE_EQ(dataset.cell(0, 1), "Joe");
        REQUIRE_EQ(dataset.cell(0, 2), "38");
        REQUIRE_EQ(dataset.cell(0, 3), "M");
        REQUIRE_EQ(dataset.cell(0, 4), "C");
        REQUIRE_EQ(dataset.cell(0, 5), "10");

        REQUIRE_EQ(dataset.cell(1, 0), "2");
        REQUIRE_EQ(dataset.cell(1, 1), "Alice");
        REQUIRE_EQ(dataset.cell(1, 2), "24");
        REQUIRE_EQ(dataset.cell(1, 3), "F");
        REQUIRE_EQ(dataset.cell(1, 4), "A");
        REQUIRE_EQ(dataset.cell(1, 5), "7.5");

        REQUIRE_EQ(dataset.cell(2, 0), "3");
        REQUIRE_EQ(dataset.cell(2, 1), "Bob");
        REQUIRE_EQ(dataset.cell(2, 2), "75");
        REQUIRE_EQ(dataset.cell(2, 3), "M");
        REQUIRE_EQ(dataset.cell(2, 4), "B");
        REQUIRE_EQ(dataset.cell(2, 5), "5");

        REQUIRE_EQ(dataset.cell(3, 0), "4");
        REQUIRE_EQ(dataset.cell(3, 1), "Carol");
        REQUIRE_EQ(dataset.cell(3, 2), "32");
        REQUIRE_EQ(dataset.cell(3, 3), "F");
        REQUIRE_EQ(dataset.cell(3, 4), "A");
        REQUIRE_EQ(dataset.cell(3, 5), "2");
        REQUIRE_EQ(dataset.cell(3, 5), "2");

        REQUIRE_EQ(dataset.cell(4, 0), "5");
        REQUIRE_EQ(dataset.cell(4, 1), "Dan");
        REQUIRE_EQ(dataset.cell(4, 2), "14");
        REQUIRE_EQ(dataset.cell(4, 3), "M");
        REQUIRE_EQ(dataset.cell(4, 4), "B");
        REQUIRE_EQ(dataset.cell(4, 5), "6.6");

        REQUIRE_EQ(dataset.cell(5, 0), "6");
        REQUIRE_EQ(dataset.cell(5, 1), "Erin");
        REQUIRE_EQ(dataset.cell(5, 2), "76");
        REQUIRE_EQ(dataset.cell(5, 3), "M");
        REQUIRE_EQ(dataset.cell(5, 4), "C");
        REQUIRE_EQ(dataset.cell(5, 5), "9.1");

        REQUIRE_EQ(dataset.cell(1, "ID"), "2");
        REQUIRE_EQ(dataset.cell(1, "NAME"), "Alice");
        REQUIRE_EQ(dataset.cell(1, "AGE"), "24");
        REQUIRE_EQ(dataset.cell(1, "SEX"), "F");
        REQUIRE_EQ(dataset.cell(1, "CLASS"), "A");
        REQUIRE_EQ(dataset.cell(1, "GRADE"), "7.5");
    }

    SUBCASE("Simple CSV - Whitespace")
    {
        Dataset dataset("./test/dataset/simple-whitespace.csv");
        REQUIRE_EQ(dataset.names(), std::vector<std::string>({"ID", "NAME", "AGE"}));
        REQUIRE_EQ(dataset.cols(), 3);
        REQUIRE_EQ(dataset.rows(), 3);
        REQUIRE_EQ(dataset.cell(0, 0), "1");
        REQUIRE_EQ(dataset.cell(0, 1), "Joe");
        REQUIRE_EQ(dataset.cell(0, 2), "38");

        REQUIRE_EQ(dataset.cell(1, 0), "2");
        REQUIRE_EQ(dataset.cell(1, 1), "Alice");
        REQUIRE_EQ(dataset.cell(1, 2), "24");

        REQUIRE_EQ(dataset.cell(2, 0), "3");
        REQUIRE_EQ(dataset.cell(2, 1), "Bob");
        REQUIRE_EQ(dataset.cell(2, 2), "75");
    }

    SUBCASE("Simple CSV - Escaped")
    {
        Dataset dataset("./test/dataset/escaped.csv");
        REQUIRE_EQ(dataset.names(), std::vector<std::string>({"ID", "NAME", "AGE"}));
        REQUIRE_EQ(dataset.cols(), 3);
        REQUIRE_EQ(dataset.rows(), 3);
        REQUIRE_EQ(dataset.cell(0, 0), "1");
        REQUIRE_EQ(dataset.cell(0, 1), "Doe, Joe");
        REQUIRE_EQ(dataset.cell(0, 2), "38");

        REQUIRE_EQ(dataset.cell(1, 0), "2");
        REQUIRE_EQ(dataset.cell(1, 1), "Alice");
        REQUIRE_EQ(dataset.cell(1, 2), "24");

        REQUIRE_EQ(dataset.cell(2, 0), "3");
        REQUIRE_EQ(dataset.cell(2, 1), "Bob");
        REQUIRE_EQ(dataset.cell(2, 2), "75");
    }

    SUBCASE("Simple CSV - New Line")
    {
        Dataset dataset("./test/dataset/escaped-crlf.csv");
        REQUIRE_EQ(dataset.names(), std::vector<std::string>({"ID", "NAME", "AGE"}));
        REQUIRE_EQ(dataset.cols(), 3);
        REQUIRE_EQ(dataset.rows(), 3);
        REQUIRE_EQ(dataset.cell(0, 0), "1");
        REQUIRE_EQ(dataset.cell(0, 1), "Doe\r\nJoe");
        REQUIRE_EQ(dataset.cell(0, 2), "38");

        REQUIRE_EQ(dataset.cell(1, 0), "2");
        REQUIRE_EQ(dataset.cell(1, 1), "Alice");
        REQUIRE_EQ(dataset.cell(1, 2), "24");

        REQUIRE_EQ(dataset.cell(2, 0), "3");
        REQUIRE_EQ(dataset.cell(2, 1), "Bob");
        REQUIRE_EQ(dataset.cell(2, 2), "75");
    }

    SUBCASE("Simple CSV - Quotes")
    {
        Dataset dataset("./test/dataset/escaped-with-quotes.csv");
        REQUIRE_EQ(dataset.names(), std::vector<std::string>({"ID", "NAME", "AGE"}));
        REQUIRE_EQ(dataset.cols(), 3);
        REQUIRE_EQ(dataset.rows(), 3);
        REQUIRE_EQ(dataset.cell(0, 0), "1");
        REQUIRE_EQ(dataset.cell(0, 1), "Doe \"Joe\"");
        REQUIRE_EQ(dataset.cell(0, 2), "38");

        REQUIRE_EQ(dataset.cell(1, 0), "2");
        REQUIRE_EQ(dataset.cell(1, 1), "Alice");
        REQUIRE_EQ(dataset.cell(1, 2), "24");

        REQUIRE_EQ(dataset.cell(2, 0), "3");
        REQUIRE_EQ(dataset.cell(2, 1), "Bob");
        REQUIRE_EQ(dataset.cell(2, 2), "75");
    }
}

TEST_CASE("Spliting dataset")
{
    SUBCASE("By Column")
    {
        Dataset dataset("./test/dataset/simple.csv");
        Dataset x = dataset.split(std::vector<std::string>({"ID", "NAME"}));
        REQUIRE_EQ(x.names(), std::vector<std::string>({"ID", "NAME"}));
        REQUIRE_EQ(x.cols(), 2);
        REQUIRE_EQ(x.rows(), 6);

        REQUIRE_EQ(x.cell(0, 0), "1");
        REQUIRE_EQ(x.cell(0, 1), "Joe");

        REQUIRE_EQ(x.cell(1, 0), "2");
        REQUIRE_EQ(x.cell(1, 1), "Alice");

        REQUIRE_EQ(x.cell(2, 0), "3");
        REQUIRE_EQ(x.cell(2, 1), "Bob");

        REQUIRE_EQ(x.cell(3, 0), "4");
        REQUIRE_EQ(x.cell(3, 1), "Carol");

        REQUIRE_EQ(x.cell(4, 0), "5");
        REQUIRE_EQ(x.cell(4, 1), "Dan");

        REQUIRE_EQ(x.cell(5, 0), "6");
        REQUIRE_EQ(x.cell(5, 1), "Erin");

        REQUIRE_EQ(x.cell(1, "ID"), "2");
        REQUIRE_EQ(x.cell(1, "NAME"), "Alice");
    }

    SUBCASE("By Row")
    {
        Dataset dataset("./test/dataset/simple.csv");
        Pair<Dataset> pair = dataset.split(0.33);
        REQUIRE_EQ(pair.first.names(), std::vector<std::string>({"ID", "NAME", "AGE", "SEX", "CLASS", "GRADE"}));
        REQUIRE_EQ(pair.second.names(), std::vector<std::string>({"ID", "NAME", "AGE", "SEX", "CLASS", "GRADE"}));

        REQUIRE_EQ(pair.first.rows(), 2);
        REQUIRE_EQ(pair.second.rows(), 4);
    }
}