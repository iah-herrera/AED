#ifndef PUNTO_INCLUIDO
#define PUNTO_INCLUIDO

#include <cmath>            //importa (depende de)
#include"FuncionesAux.h"    //importa (depende de)

//conj de valores
struct Punto    
{
    double x, y;
};

//declaracion del conjunto de ops
double GetDistancia(const Punto&, const Punto&);
bool SonIguales(const Punto&, const Punto&);


//implementacion del conjunto de ops
double GetDistancia(const Punto &p1, const Punto &p2)
{
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

bool SonIguales(const Punto &a, const Punto &b) //Se desarrolla esta funcion porque sirve para verificar y tambien para ejecutar dentro de otras funciones
{
    if (AreNear(a.x, b.x) and AreNear(a.y, b.y))
        return true;
    else
        return false;
}

#endif 
