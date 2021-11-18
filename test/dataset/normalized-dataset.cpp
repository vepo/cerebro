#include "doctest.h"

#include "dataset/dataset.hpp"

TEST_CASE("Reading dataset")
{
    Dataset dataset = Dataset("./test/dataset/simple.csv");
    NormalizedDataset nd = dataset.normalize();

    CHECK_EQ(nd.type(0), DataType::INTEGER);
    CHECK_EQ(nd.type(1), DataType::STRING);
    CHECK_EQ(nd.type(2), DataType::INTEGER);
    CHECK_EQ(nd.type(3), DataType::BOOLEAN);
    CHECK_EQ(nd.type(4), DataType::ENUM);
    CHECK_EQ(nd.type(5), DataType::FLOATING_POINT);
    
    CHECK_EQ(nd.type("ID"), DataType::INTEGER);
    CHECK_EQ(nd.type("NAME"), DataType::STRING);
    CHECK_EQ(nd.type("AGE"), DataType::INTEGER);
    CHECK_EQ(nd.type("SEX"), DataType::BOOLEAN);
    CHECK_EQ(nd.type("CLASS"), DataType::ENUM);
    CHECK_EQ(nd.type("GRADE"), DataType::FLOATING_POINT);

    // ID
    CHECK_EQ(nd.cell(0, 0), 0.0);
    CHECK_EQ(nd.cell(1, 0), 0.2);
    CHECK_EQ(nd.cell(2, 0), 0.4);
    CHECK_EQ(nd.cell(3, 0), 0.6);
    CHECK_EQ(nd.cell(4, 0), 0.8);
    CHECK_EQ(nd.cell(5, 0), 1.0);

    CHECK_EQ(nd.cell(0, "ID"), 0.0);
    CHECK_EQ(nd.cell(1, "ID"), 0.2);
    CHECK_EQ(nd.cell(2, "ID"), 0.4);
    CHECK_EQ(nd.cell(3, "ID"), 0.6);
    CHECK_EQ(nd.cell(4, "ID"), 0.8);
    CHECK_EQ(nd.cell(5, "ID"), 1.0);

    // NAME

    // AGE
    CHECK_EQ(doctest::Approx(nd.cell(0, 2)).epsilon(0.0001), 0.387097);
    CHECK_EQ(doctest::Approx(nd.cell(1, 2)).epsilon(0.0001), 0.16129);
    CHECK_EQ(doctest::Approx(nd.cell(2, 2)).epsilon(0.0001), 0.983871);
    CHECK_EQ(doctest::Approx(nd.cell(3, 2)).epsilon(0.0001), 0.290323);
    CHECK_EQ(doctest::Approx(nd.cell(4, 2)).epsilon(0.0001), 0.0);
    CHECK_EQ(doctest::Approx(nd.cell(5, 2)).epsilon(0.0001), 1.0);

    CHECK_EQ(doctest::Approx(nd.cell(0, "AGE")).epsilon(0.0001), 0.387097);
    CHECK_EQ(doctest::Approx(nd.cell(1, "AGE")).epsilon(0.0001), 0.16129);
    CHECK_EQ(doctest::Approx(nd.cell(2, "AGE")).epsilon(0.0001), 0.983871);
    CHECK_EQ(doctest::Approx(nd.cell(3, "AGE")).epsilon(0.0001), 0.290323);
    CHECK_EQ(doctest::Approx(nd.cell(4, "AGE")).epsilon(0.0001), 0.0);
    CHECK_EQ(doctest::Approx(nd.cell(5, "AGE")).epsilon(0.0001), 1.0);

    // SEX
    CHECK_EQ(nd.cell(0, 3), 1.0);
    CHECK_EQ(nd.cell(1, 3), 0.0);
    CHECK_EQ(nd.cell(2, 3), 1.0);
    CHECK_EQ(nd.cell(3, 3), 0.0);
    CHECK_EQ(nd.cell(4, 3), 1.0);
    CHECK_EQ(nd.cell(5, 3), 1.0);

    CHECK_EQ(nd.cell(0, "SEX"), 1.0);
    CHECK_EQ(nd.cell(1, "SEX"), 0.0);
    CHECK_EQ(nd.cell(2, "SEX"), 1.0);
    CHECK_EQ(nd.cell(3, "SEX"), 0.0);
    CHECK_EQ(nd.cell(4, "SEX"), 1.0);
    CHECK_EQ(nd.cell(5, "SEX"), 1.0);

    // CLASS
    CHECK_EQ(doctest::Approx(nd.cell(0, 4)).epsilon(0.01), 0.0);
    CHECK_EQ(doctest::Approx(nd.cell(1, 4)).epsilon(0.01), 0.5);
    CHECK_EQ(doctest::Approx(nd.cell(2, 4)).epsilon(0.01), 1.0);
    CHECK_EQ(doctest::Approx(nd.cell(3, 4)).epsilon(0.01), 0.5);
    CHECK_EQ(doctest::Approx(nd.cell(4, 4)).epsilon(0.01), 1.0);
    CHECK_EQ(doctest::Approx(nd.cell(5, 4)).epsilon(0.01), 0.0);

    CHECK_EQ(doctest::Approx(nd.cell(0, "CLASS")).epsilon(0.01), 0.0);
    CHECK_EQ(doctest::Approx(nd.cell(1, "CLASS")).epsilon(0.01), 0.5);
    CHECK_EQ(doctest::Approx(nd.cell(2, "CLASS")).epsilon(0.01), 1.0);
    CHECK_EQ(doctest::Approx(nd.cell(3, "CLASS")).epsilon(0.01), 0.5);
    CHECK_EQ(doctest::Approx(nd.cell(4, "CLASS")).epsilon(0.01), 1.0);
    CHECK_EQ(doctest::Approx(nd.cell(5, "CLASS")).epsilon(0.01), 0.0);
}