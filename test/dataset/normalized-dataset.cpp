#include "doctest.h"

#include "dataset/dataset.hpp"

#include <iostream>

TEST_CASE("Reading dataset")
{
    Dataset dataset = Dataset("./test/dataset/simple.csv");
    NormalizedDataset nd = dataset.normalize();

    REQUIRE_EQ(dataset.type(0), DataType::INTEGER);
    REQUIRE_EQ(dataset.type(1), DataType::ENUM);
    REQUIRE_EQ(dataset.type(2), DataType::INTEGER);
    REQUIRE_EQ(dataset.type(3), DataType::BOOLEAN);
    REQUIRE_EQ(dataset.type(4), DataType::ENUM);
    REQUIRE_EQ(dataset.type(5), DataType::FLOATING_POINT);

    REQUIRE_EQ(dataset.type("ID"), DataType::INTEGER);
    REQUIRE_EQ(dataset.type("NAME"), DataType::ENUM);
    REQUIRE_EQ(dataset.type("AGE"), DataType::INTEGER);
    REQUIRE_EQ(dataset.type("SEX"), DataType::BOOLEAN);
    REQUIRE_EQ(dataset.type("CLASS"), DataType::ENUM);
    REQUIRE_EQ(dataset.type("GRADE"), DataType::FLOATING_POINT);

    // ID
    REQUIRE_EQ(nd.cell(0, 0), 0.0);
    REQUIRE_EQ(nd.cell(1, 0), 0.2);
    REQUIRE_EQ(nd.cell(2, 0), 0.4);
    REQUIRE_EQ(nd.cell(3, 0), 0.6);
    REQUIRE_EQ(nd.cell(4, 0), 0.8);
    REQUIRE_EQ(nd.cell(5, 0), 1.0);

    REQUIRE_EQ(nd.cell(0, "ID"), 0.0);
    REQUIRE_EQ(nd.cell(1, "ID"), 0.2);
    REQUIRE_EQ(nd.cell(2, "ID"), 0.4);
    REQUIRE_EQ(nd.cell(3, "ID"), 0.6);
    REQUIRE_EQ(nd.cell(4, "ID"), 0.8);
    REQUIRE_EQ(nd.cell(5, "ID"), 1.0);

    // NAME

    // AGE
    REQUIRE_EQ(doctest::Approx(nd.cell(0, 2)).epsilon(0.0001), 0.387097);
    REQUIRE_EQ(doctest::Approx(nd.cell(1, 2)).epsilon(0.0001), 0.16129);
    REQUIRE_EQ(doctest::Approx(nd.cell(2, 2)).epsilon(0.0001), 0.983871);
    REQUIRE_EQ(doctest::Approx(nd.cell(3, 2)).epsilon(0.0001), 0.290323);
    REQUIRE_EQ(doctest::Approx(nd.cell(4, 2)).epsilon(0.0001), 0.0);
    REQUIRE_EQ(doctest::Approx(nd.cell(5, 2)).epsilon(0.0001), 1.0);
    
    REQUIRE_EQ(doctest::Approx(nd.cell(0, "AGE")).epsilon(0.0001), 0.387097);
    REQUIRE_EQ(doctest::Approx(nd.cell(1, "AGE")).epsilon(0.0001), 0.16129);
    REQUIRE_EQ(doctest::Approx(nd.cell(2, "AGE")).epsilon(0.0001), 0.983871);
    REQUIRE_EQ(doctest::Approx(nd.cell(3, "AGE")).epsilon(0.0001), 0.290323);
    REQUIRE_EQ(doctest::Approx(nd.cell(4, "AGE")).epsilon(0.0001), 0.0);
    REQUIRE_EQ(doctest::Approx(nd.cell(5, "AGE")).epsilon(0.0001), 1.0);
    
    // SEX
    REQUIRE_EQ(nd.cell(0, 3), 0.5);
    REQUIRE_EQ(nd.cell(1, 3), 1.0);
    REQUIRE_EQ(nd.cell(2, 3), 0.5);
    REQUIRE_EQ(nd.cell(3, 3), 1.0);
    REQUIRE_EQ(nd.cell(4, 3), 0.5);
    REQUIRE_EQ(nd.cell(5, 3), 0.5);
    
    REQUIRE_EQ(nd.cell(0, "SEX"), 0.5);
    REQUIRE_EQ(nd.cell(1, "SEX"), 1.0);
    REQUIRE_EQ(nd.cell(2, "SEX"), 0.5);
    REQUIRE_EQ(nd.cell(3, "SEX"), 1.0);
    REQUIRE_EQ(nd.cell(4, "SEX"), 0.5);
    REQUIRE_EQ(nd.cell(5, "SEX"), 0.5);
    
    // CLASS
    REQUIRE_EQ(doctest::Approx(nd.cell(0, 4)).epsilon(0.01), 1.00); // C -> 3
    REQUIRE_EQ(doctest::Approx(nd.cell(1, 4)).epsilon(0.01), 0.33); // A -> 1
    REQUIRE_EQ(doctest::Approx(nd.cell(2, 4)).epsilon(0.01), 0.66); // B -> 2
    REQUIRE_EQ(doctest::Approx(nd.cell(3, 4)).epsilon(0.01), 0.33); // A -> 1
    REQUIRE_EQ(doctest::Approx(nd.cell(4, 4)).epsilon(0.01), 0.66); // B -> 2
    REQUIRE_EQ(doctest::Approx(nd.cell(5, 4)).epsilon(0.01), 1.00); // C -> 3
    
    REQUIRE_EQ(doctest::Approx(nd.cell(0, "CLASS")).epsilon(0.01), 1.00);  // C
    REQUIRE_EQ(doctest::Approx(nd.cell(1, "CLASS")).epsilon(0.01), 0.33);  // A
    REQUIRE_EQ(doctest::Approx(nd.cell(2, "CLASS")).epsilon(0.01), 0.66);  // B
    REQUIRE_EQ(doctest::Approx(nd.cell(3, "CLASS")).epsilon(0.01), 0.33);  // A
    REQUIRE_EQ(doctest::Approx(nd.cell(4, "CLASS")).epsilon(0.01), 0.66);  // B
    REQUIRE_EQ(doctest::Approx(nd.cell(5, "CLASS")).epsilon(0.01), 1.00);  // C
}