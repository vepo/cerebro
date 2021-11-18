#include "doctest.h"

#include "dataset/dataset.hpp"

TEST_CASE("Reading dataset")
{
    SUBCASE("Simple CSV")
    {
        Dataset dataset = Dataset("./test/dataset/simple.csv");
        CHECK_EQ(dataset.names, std::vector<std::string>({"ID", "NAME", "AGE", "SEX", "CLASS", "GRADE"}));
        CHECK_EQ(dataset.cols, 6);
        CHECK_EQ(dataset.rows, 6);
        CHECK_EQ(dataset.cell(0, 0), "1");
        CHECK_EQ(dataset.cell(0, 1), "Joe");
        CHECK_EQ(dataset.cell(0, 2), "38");
        CHECK_EQ(dataset.cell(0, 3), "M");
        CHECK_EQ(dataset.cell(0, 4), "C");
        CHECK_EQ(dataset.cell(0, 5), "10");

        CHECK_EQ(dataset.cell(1, 0), "2");
        CHECK_EQ(dataset.cell(1, 1), "Alice");
        CHECK_EQ(dataset.cell(1, 2), "24");
        CHECK_EQ(dataset.cell(1, 3), "F");
        CHECK_EQ(dataset.cell(1, 4), "A");
        CHECK_EQ(dataset.cell(1, 5), "7.5");

        CHECK_EQ(dataset.cell(2, 0), "3");
        CHECK_EQ(dataset.cell(2, 1), "Bob");
        CHECK_EQ(dataset.cell(2, 2), "75");
        CHECK_EQ(dataset.cell(2, 3), "M");
        CHECK_EQ(dataset.cell(2, 4), "B");
        CHECK_EQ(dataset.cell(2, 5), "5");

        CHECK_EQ(dataset.cell(3, 0), "4");
        CHECK_EQ(dataset.cell(3, 1), "Carol");
        CHECK_EQ(dataset.cell(3, 2), "32");
        CHECK_EQ(dataset.cell(3, 3), "F");
        CHECK_EQ(dataset.cell(3, 4), "A");
        CHECK_EQ(dataset.cell(3, 5), "2");
        CHECK_EQ(dataset.cell(3, 5), "2");

        CHECK_EQ(dataset.cell(4, 0), "5");
        CHECK_EQ(dataset.cell(4, 1), "Dan");
        CHECK_EQ(dataset.cell(4, 2), "14");
        CHECK_EQ(dataset.cell(4, 3), "M");
        CHECK_EQ(dataset.cell(4, 4), "B");
        CHECK_EQ(dataset.cell(4, 5), "6.6");

        CHECK_EQ(dataset.cell(5, 0), "6");
        CHECK_EQ(dataset.cell(5, 1), "Erin");
        CHECK_EQ(dataset.cell(5, 2), "76");
        CHECK_EQ(dataset.cell(5, 3), "M");
        CHECK_EQ(dataset.cell(5, 4), "C");
        CHECK_EQ(dataset.cell(5, 5), "9.1");

        CHECK_EQ(dataset.cell(1, "ID"), "2");
        CHECK_EQ(dataset.cell(1, "NAME"), "Alice");
        CHECK_EQ(dataset.cell(1, "AGE"), "24");
        CHECK_EQ(dataset.cell(1, "SEX"), "F");
        CHECK_EQ(dataset.cell(1, "CLASS"), "A");
        CHECK_EQ(dataset.cell(1, "GRADE"), "7.5");
    }

    SUBCASE("Simple CSV - Whitespace")
    {
        Dataset dataset = Dataset("./test/dataset/simple-whitespace.csv");
        CHECK_EQ(dataset.names, std::vector<std::string>({"ID", "NAME", "AGE"}));
        CHECK_EQ(dataset.cols, 3);
        CHECK_EQ(dataset.rows, 3);
        CHECK_EQ(dataset.cell(0, 0), "1");
        CHECK_EQ(dataset.cell(0, 1), "Joe");
        CHECK_EQ(dataset.cell(0, 2), "38");

        CHECK_EQ(dataset.cell(1, 0), "2");
        CHECK_EQ(dataset.cell(1, 1), "Alice");
        CHECK_EQ(dataset.cell(1, 2), "24");

        CHECK_EQ(dataset.cell(2, 0), "3");
        CHECK_EQ(dataset.cell(2, 1), "Bob");
        CHECK_EQ(dataset.cell(2, 2), "75");
    }

    SUBCASE("Simple CSV - Escaped")
    {
        Dataset dataset = Dataset("./test/dataset/escaped.csv");
        CHECK_EQ(dataset.names, std::vector<std::string>({"ID", "NAME", "AGE"}));
        CHECK_EQ(dataset.cols, 3);
        CHECK_EQ(dataset.rows, 3);
        CHECK_EQ(dataset.cell(0, 0), "1");
        CHECK_EQ(dataset.cell(0, 1), "Doe, Joe");
        CHECK_EQ(dataset.cell(0, 2), "38");

        CHECK_EQ(dataset.cell(1, 0), "2");
        CHECK_EQ(dataset.cell(1, 1), "Alice");
        CHECK_EQ(dataset.cell(1, 2), "24");

        CHECK_EQ(dataset.cell(2, 0), "3");
        CHECK_EQ(dataset.cell(2, 1), "Bob");
        CHECK_EQ(dataset.cell(2, 2), "75");
    }

    SUBCASE("Simple CSV - New Line")
    {
        Dataset dataset = Dataset("./test/dataset/escaped-crlf.csv");
        CHECK_EQ(dataset.names, std::vector<std::string>({"ID", "NAME", "AGE"}));
        CHECK_EQ(dataset.cols, 3);
        CHECK_EQ(dataset.rows, 3);
        CHECK_EQ(dataset.cell(0, 0), "1");
        CHECK_EQ(dataset.cell(0, 1), "Doe\r\nJoe");
        CHECK_EQ(dataset.cell(0, 2), "38");

        CHECK_EQ(dataset.cell(1, 0), "2");
        CHECK_EQ(dataset.cell(1, 1), "Alice");
        CHECK_EQ(dataset.cell(1, 2), "24");

        CHECK_EQ(dataset.cell(2, 0), "3");
        CHECK_EQ(dataset.cell(2, 1), "Bob");
        CHECK_EQ(dataset.cell(2, 2), "75");
    }

    SUBCASE("Simple CSV - Quotes")
    {
        Dataset dataset = Dataset("./test/dataset/escaped-with-quotes.csv");
        CHECK_EQ(dataset.names, std::vector<std::string>({"ID", "NAME", "AGE"}));
        CHECK_EQ(dataset.cols, 3);
        CHECK_EQ(dataset.rows, 3);
        CHECK_EQ(dataset.cell(0, 0), "1");
        CHECK_EQ(dataset.cell(0, 1), "Doe \"Joe\"");
        CHECK_EQ(dataset.cell(0, 2), "38");

        CHECK_EQ(dataset.cell(1, 0), "2");
        CHECK_EQ(dataset.cell(1, 1), "Alice");
        CHECK_EQ(dataset.cell(1, 2), "24");

        CHECK_EQ(dataset.cell(2, 0), "3");
        CHECK_EQ(dataset.cell(2, 1), "Bob");
        CHECK_EQ(dataset.cell(2, 2), "75");
    }
}

TEST_CASE("Spliting dataset")
{
    SUBCASE("By Column")
    {
        Dataset dataset = Dataset("./test/dataset/simple.csv");
        Dataset x = dataset.split(std::vector<std::string>({"ID", "NAME"}));
        CHECK_EQ(x.names, std::vector<std::string>({"ID", "NAME"}));
        CHECK_EQ(x.cols, 2);
        CHECK_EQ(x.rows, 6);

        CHECK_EQ(x.cell(0, 0), "1");
        CHECK_EQ(x.cell(0, 1), "Joe");

        CHECK_EQ(x.cell(1, 0), "2");
        CHECK_EQ(x.cell(1, 1), "Alice");

        CHECK_EQ(x.cell(2, 0), "3");
        CHECK_EQ(x.cell(2, 1), "Bob");

        CHECK_EQ(x.cell(3, 0), "4");
        CHECK_EQ(x.cell(3, 1), "Carol");

        CHECK_EQ(x.cell(4, 0), "5");
        CHECK_EQ(x.cell(4, 1), "Dan");

        CHECK_EQ(x.cell(5, 0), "6");
        CHECK_EQ(x.cell(5, 1), "Erin");

        CHECK_EQ(x.cell(1, "ID"), "2");
        CHECK_EQ(x.cell(1, "NAME"), "Alice");
    }

    SUBCASE("By Row")
    {
        Dataset dataset = Dataset("./test/dataset/simple.csv");
        Pair<Dataset> pair = dataset.split(0.33);
        CHECK_EQ(pair.first.names, std::vector<std::string>({"ID", "NAME", "AGE", "SEX", "CLASS", "GRADE"}));
        CHECK_EQ(pair.second.names, std::vector<std::string>({"ID", "NAME", "AGE", "SEX", "CLASS", "GRADE"}));

        CHECK_EQ(pair.first.rows, 2);
        CHECK_EQ(pair.second.rows, 4);
    }
}