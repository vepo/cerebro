#pragma once

#include <string>
#include <vector>

#include "dataset/normalized-dataset.hpp"
#include "utils/pair.hpp"

class Dataset
{
public:
    explicit Dataset(std::string const &path);
    std::string cell(int row, int col);
    std::string cell(int row, const std::string &colName);

    int cols;
    int rows;
    std::vector<std::vector<std::string>> contents;
    std::vector<std::string> names;
    Dataset split(const std::vector<std::string> &columnNames);
    Dataset split(const std::vector<int> &colums);
    Pair<Dataset> split(double ratio);
    NormalizedDataset normalize();

private:
    int colIndex(const std::string &colName);
    Dataset(const std::vector<std::string> &names,
            const std::vector<std::vector<std::string>> &contents);
};