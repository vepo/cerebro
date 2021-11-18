#pragma once

template <class TYPE>
class Pair
{
public:
    Pair(TYPE f, const TYPE s) : first(f), second(s){};

    TYPE first;
    TYPE second;
};