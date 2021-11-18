#include "utils/random.hpp"

#include <random>

int Random::randomInteger()
{
    return std::rand();
}

template <class T>
T Random::chooseItem(std::vector<T> const &data)
{
    return data[std::rand() % data.size()];
}