#include "utils/random.hpp"

#include <random>

std::random_device rd;
std::mt19937 mt(rd());

std::uniform_int_distribution<int> integerDist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
std::uniform_real_distribution<double> doubleDist(-1.0, 1.0);

int Random::randomInteger()
{
    return integerDist(mt);
}

double Random::randomDouble()
{
    return doubleDist(mt);
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