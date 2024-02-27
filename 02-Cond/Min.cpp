/*
    Min.cpp
    TP02 Cond
    Grupo 12
    Valor mínimo entre dos valores:
    Min: ZxZ -->Z/ min(a,b) =   { a  a < b
                                { b  e.o.c
*/

#include <cassert>

int Min(int, int);

int main()
{
    assert(0 == Min(0, 0));
    assert(-1 == Min(-1, -1));
    assert(3 == Min(3, 10));
    assert(-3 == Min(-3, 3));
}

int Min(int a, int b)
{
    return a < b ? a : b;
}
