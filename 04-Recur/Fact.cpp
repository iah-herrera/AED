/*
    04-Recur-Fact.cpp
    TP04 Recursividad - Función Fact
    Grupo 12
    06/07/23
*/

#include <iostream>
#include <cassert>


// La funcion factorial crece muy rápido D: entonces utilizamos el tipo de dato unsigned long long
unsigned long long Fact(unsigned n); // n es el número al que se le quiere calcular el factorial

int main()
{    
    assert(Fact(0)==1);
    assert(Fact(5)==120);
    assert(Fact(20)==2432902008176640000);
    assert(Fact(21)==14197454024290336768);
   /*
        Este número es tan grande que se pasa dos veces el límite de este tipo de dato
        se puede llegar a él realizando 21!-2*(límite del tipo de dato)
        Donde el límite es cercano a 1,8845 x 10 ^ 19
   */ 
   return 0;
}

unsigned long long Fact(unsigned n)
{
    return (n==0)?1:n*Fact(n-1);
}
