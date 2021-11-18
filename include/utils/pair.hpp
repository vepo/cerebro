#pragma once

template <class TYPE>
class Pair
{
public:
    Pair(const TYPE &f, const TYPE &s) : first(f), second(s){};

    const TYPE &first;
    const TYPE &second;
};