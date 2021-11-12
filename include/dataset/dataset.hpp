#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Dataset
{
public:
    Dataset(string path);
    string path;
    vector<string> names;
};