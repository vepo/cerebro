#include "dataset/dataset.hpp"

Dataset::Dataset(string path)
{
    this->path = path;
    this->names.push_back("ID");
    this->names.push_back("NAME");
    this->names.push_back("AGE");
}