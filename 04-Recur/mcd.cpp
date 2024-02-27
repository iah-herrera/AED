/*
    mcd.cpp
    TP04 Recursividad - Función mcd
    Grupo 12
    06/07/23
    Definicion matematica:

    a y b petenecen a Z
    El mcd(a, b) es el máximo número entero positivo que divide exactamente a ambos a y b.

*/

#include <cassert>

int mcd(int, int);

int main()
{
    assert(mcd(224, 120) == 8);
    assert(mcd(300, 168) == 12);
    assert(mcd(162, -48) == 6);
    assert(mcd(105, 140) == 35);
}

int mcd(int a, int b)
{
    return (b == 0) ? a : mcd(b, a % b);
};