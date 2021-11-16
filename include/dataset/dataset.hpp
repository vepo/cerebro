#pragma once

#include <string>
#include <vector>

#include "dataset/normalized-dataset.hpp"
#include "utils/pair.hpp"

class Dataset
{
public:
    Dataset(std::string const &path);
    std::string cell(int row, int col);
    std::string cell(int row, std::string colName);
    int colIndex(std::string colName);

    int cols;
    int rows;
    std::vector<std::string> names;
    Dataset split(std::vector<std::string> columnNames);
    Dataset split(std::vector<int> colums);
    Pair<Dataset> split(double ratio);
    NormalizedDataset normalize();

private:
    Dataset(std::vector<std::string> names, std::vector<std::vector<std::string>> contents);
    std::vector<std::vector<std::string>> contents;
};