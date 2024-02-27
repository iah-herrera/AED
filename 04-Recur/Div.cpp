/*
    04-Recur-Div.cpp
    TP04 Recursividad - Función Div
    Grupo 12
    06/07/23
*/

#include <iostream>
#include <cassert>

int main()
{    
    assert(0 == Div(1000,2000));
    assert(2 == Div(7,3));
    assert(3 == Div(30,10));
    assert(4 == Div(20,5));
    assert(5 == Div(100,20));
   return 0;
}

unsigned Div(unsigned num, unsigned den)
{
    return (num < den) ? 0 : Div(num - den, den) + 1;
}
