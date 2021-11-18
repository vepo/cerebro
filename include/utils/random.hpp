#pragma once

#include <vector>

class Random
{
public:
    static int randomInteger();
    template <class T>
    static T chooseItem(std::vector<T> const &data);
};