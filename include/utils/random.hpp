#pragma once

#include <vector>

class Random
{
public:
    static double randomDouble();
    static int randomInteger();
    static int randomInteger(int maxExclusive);
    template <class T>
    static T chooseItem(std::vector<T> const &data);
};