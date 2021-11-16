#pragma once

#include <vector>
#include <string>

using namespace std;

enum DataType
{
    STRING = 1,
    INTEGER = 2,
    FLOATING_POINT = 3,
    ENUM = 4,
    BOOLEAN = 5,
    TEXT = 6
};

class NormalizedDataset
{
public:
    NormalizedDataset(vector<string> names,
                      vector<vector<string>> contents);
    double cell(int row, int col);
    double cell(int row, string colName);
    DataType type(int col);
    DataType type(string colName);

private:
    vector<string> names;
    vector<vector<double>> contents;
    vector<DataType> types;
};