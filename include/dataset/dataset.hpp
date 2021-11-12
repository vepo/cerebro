#pragma once

#include <string>
#include <vector>

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
    string path;
    vector<string> names;

private:
    vector<vector<string>> contents;
};