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

    Dataset split(const std::vector<std::string> &columnNames);
    Dataset split(const std::vector<int> &colums);
    Pair<Dataset> split(double ratio);
    NormalizedDataset normalize();
    const std::vector<std::string> &names() { return this->_names; };
    int cols() { return this->_cols; };
    int rows() { return this->_rows; };

private:
    std::vector<std::string> _names;
    std::vector<std::vector<std::string>> _contents;
    int _cols;
    int _rows;
    int colIndex(const std::string &colName);
    Dataset(const std::vector<std::string> &names,
            const std::vector<std::vector<std::string>> &contents);
};