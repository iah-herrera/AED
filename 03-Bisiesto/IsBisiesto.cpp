/*
    IsBisiesto.cpp
    TP03 Precedencia de Operadores — Bisiesto
    Grupo 12
    Desarrollar una función que dado un año, determine si es bisiesto:

    IsBisiesto : N --> B  /  IsBisiesto(anio)  =    anio % 4 == 0 and (anio % 100 != 0 or anio % 400 == 0)
    Precondicion: D isBisiesto = N - [0;1582) y calendario gregoriano

*/

#include <cassert>

bool IsBisiesto(unsigned); // declaracion de la funcion

int main()
{
    assert(IsBisiesto(1848));
    assert(IsBisiesto(1904));
    assert(IsBisiesto(2020));
    assert(IsBisiesto(2000));
    assert(IsBisiesto(2024));
    assert(IsBisiesto(1600));
    assert(IsBisiesto(1972));
    assert(not IsBisiesto(1700));
    assert(not IsBisiesto(1800));
    assert(not IsBisiesto(1899));
    assert(not IsBisiesto(1900));
    assert(not IsBisiesto(1957));
    assert(not IsBisiesto(2018));
    assert(not IsBisiesto(2023));
}

bool IsBisiesto(unsigned anio) // definicion de la funcion
{
    return anio % 4 == 0 and (anio % 100 != 0 or anio % 400 == 0);
}
