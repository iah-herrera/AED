/*
    abs.cpp
    TP02 Cond
    Grupo 12
    Valor absoluto:
    abs: Z --> Z / abs(a) = { -a  a < 0
                            {  a  e.o.c
*/

#include <iostream>
#include <cassert>

int abs(int);

int main()
{
    std::cout << abs(-3);
    assert(3 == abs(-3));
    assert(0 == abs(0));
    assert(3 == abs(3));
}

int abs(int x)
{
    return x < 0 ? -x : x;
}
