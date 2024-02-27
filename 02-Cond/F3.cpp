/*
    F3.cpp
    TP02 Cond
    Grupo 12
    Funsión F3 definida por partes:
    f3 : R --> R  /  f3(x)  = {  x   si   x > 3
                              { -x   si  -3 <= x <= 3
                              {  x   si   x < -3

    Casos de prueba:
    f3(4) = 4
    f3(2) = -2
    f3(3) = -3
    f3(-4) = -4
    f3(-3.5) = -3.5
*/

#include <cassert>

double f3(double); // declaracion de la funcion

int main()
{
    assert(4 == f3(4));
    assert(-2 == f3(2));
    assert(-3 == f3(3));
    assert(-4 == f3(-4));
    assert(-3.5 == f3(-3.5));
    assert(-3 == f3(3));
}
double f3(double x) // definicion de la funcion
{
    return (-3 <= x and x <= 3) ? -x : x;
}
