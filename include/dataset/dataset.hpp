#pragma once

#include <string>
#include <vector>

#include "dataset/normalized-dataset.hpp"
#include "utils/pair.hpp"

using namespace std;

class Dataset
{
public:
    Dataset(string path);
    string cell(int row, int col);
    string cell(int row, string colName);
    int colIndex(string colName);

    int cols;
    int rows;
    vector<string> names;
    Dataset split(vector<string> columnNames);
    Dataset split(vector<int> colums);
    Pair<Dataset> split(double ratio);
    NormalizedDataset normalize();

private:
    Dataset(vector<string> names, vector<vector<string>> contents);
    vector<vector<string>> contents;
};