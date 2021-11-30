#pragma once

#include "dataset/normalizer.hpp"

#include <vector>
#include <string>
#include <map>

class NormalizedDataset
{
public:
    NormalizedDataset(const std::vector<std::string> &names,
                      const std::vector<std::vector<double>> &contents);
    double cell(int row, int col);
    double cell(int row, const std::string &colName);
    std::vector<double> rowData(int row) const;
    int rows() const { return this->_contents.size(); };

private:
    int colIndex(const std::string &colName);
    std::vector<std::string> _names;
    std::vector<std::vector<double>> _contents;
};