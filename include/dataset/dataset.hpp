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
    vector<string> names;
    Dataset split(vector<string> columnNames);
    Dataset split(vector<int> colums);

private:
    Dataset(vector<string> names,vector<vector<string>> contents);
    vector<vector<string>> contents;
};