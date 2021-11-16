#pragma once

template <class T>
class Pair
{
public:
    Pair(T f, T s) : first(f), second(s) {}

    T first;
    T second;
};