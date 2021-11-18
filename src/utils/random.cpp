#include "utils/random.hpp"

#include <random>
#include <climits>

std::mt19937 mt(1729);
std::uniform_int_distribution<int> integerDist(INT_MIN, INT_MAX);
int Random::randomInteger()
{
    return integerDist(mt);
}

int Random::randomInteger(int maxExclusive)
{
    std::uniform_int_distribution<int> dist(0, maxExclusive - 1);
    return dist(mt);
}

template <class T>
T Random::chooseItem(std::vector<T> const &data)
{
    return data[randomInteger(data.size())];
}