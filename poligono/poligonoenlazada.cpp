/**
 * @file poligonoenlazada.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <cassert>
#include <array>

using std::array;

// Declarion estructuras

struct Punto
{
    double x, y;
};

struct Nodo
{
    Punto Puntos;
    Nodo* next;
};

struct Poligono {
    Nodo* Primero
};








/***********************   Declaracion de Funciones     *********************/

// Perimetro: Poligono -> R

// cantidad de lados: Poligono -> N
unsigned CantidadDeLados(const Poligono &);

// Esan Solapados: poligono X poligono -> bool
bool EstanSolapados(const Poligono &, const Poligono &);

// Son Iguales: Punto X Punto -> B
bool SonIguales(const Punto &, const Punto &);
bool AreNear(const double &, const double &, double = 0.0001);

// push: Poligono X Punto -> Poligono
void Push(Poligono &, const Punto &);

// push: Poligono X Punto -> Poligono - por composicion de funciones fluida
Poligono &Push2(Poligono &, const Punto &);

// pop: Poligono -> Poligono x Punto
Poligono &Pop(Poligono &, const Punto &);

// pop: Poligono -> Poligono
void Pop(Poligono &);

// pop2: Poligono -> Poligono - por composidicon de funciones fluida
Poligono &Pop2(Poligono &);

// Top: Poligono -> Punto
Punto Top(const Poligono);

// Add: Poligono X Punto X N -> Poligono
void Add(Poligono &, const Punto &, const unsigned &);

// Pos: Poligono X Punto -> N
unsigned Pos(const Poligono &, const Punto &);

// Get: Poligono X N -> Punto
Punto Get(const Poligono &, const unsigned &);

// Remove: Poligono X N -> Poligono
Poligono &Remove(Poligono &, const unsigned &);

// Remove: Poligono X Punto -> Poligono
Poligono &Remove2(Poligono &, const Punto &);

// Set: Poligono X N X Punto -> Poligono
Poligono &Set(Poligono &, const unsigned &, const Punto &);




///*********************      Main         *************************/

/* int main()
{
    Poligono p{};
    Push2(Push2(Push2(p, {5, 8}), {3.4, 8.4}), {5.5, 6.7});
    Punto a{Top(p)};
    assert(CantidadDeLados(p) == 3);
    assert(SonIguales(a, Top(p)));
    Add(p, {8, 8}, 2);
    Add(p, {6.8, 8.7}, 50);
    assert(CantidadDeLados(Pop2(p)) == 4);
    assert(Pos(p, {8, 8}) == 2);
    assert(SonIguales({5.5, 6.7}, Get(p, 4)));
    assert(SonIguales({3.4, 8.4}, Get(p, 3)));
    Remove(p, 3);
    assert(SonIguales({5.5, 6.7}, Get(p, 3)));
    Set(p, 1, {0.5, 3.8});
    assert(SonIguales({0.5, 3.8}, Get(p, 1)));
};
 */







/* unsigned CantidadDeLados(const Poligono &Pol)
{
    return Pol.n;
};

Poligono &Push2(Poligono &Pol, const Punto &a)
{
    Pol.Puntos.at(Pol.n) = a;
    Pol.n++;
    return Pol;
};

Poligono &Pop2(Poligono &Pol)
{
    Pol.n--;
    return Pol;
};

Punto Top(const Poligono Pol)
{
    return Pol.Puntos.at(Pol.n - 1);
};

bool AreNear(const double &a, const double &b, double tolerancia)
{
    return (a - tolerancia) <= b and b <= (a + tolerancia);
};

bool SonIguales(const Punto &a, const Punto &b)
{
    if (AreNear(a.x, b.x) and AreNear(a.y, b.y))
        return true;
    else
        return false;
};

void Add(Poligono &pol, const Punto &a, const unsigned &pos)
{
    if (pos >= pol.n) // hago un push al final del array si quiero poner el punto en la ultima posicion o en una posicion superior
    {
        Push2(pol, a);
        // return;
    }
    else
    {
        for (unsigned i{pol.n}; i >= pos; i--)
        {
            pol.Puntos.at(i) = pol.Puntos.at(i - 1);
        }
        pol.Puntos.at(pos - 1) = a;
        pol.n++;
        // return;
    }
};

unsigned Pos(const Poligono &pol, const Punto &a)
{
    for (unsigned i{}; i < pol.n; i++)
        if (SonIguales(a, pol.Puntos.at(i)))
            return i + 1;
    return pol.n;
};

Punto Get(const Poligono &Pol, const unsigned &pos)
{
    return Pol.Puntos.at(pos - 1);
};

Poligono &Remove(Poligono &pol, const unsigned &pos)
{
    if (pos > pol.n)
        return pol;
    else
    {
        for (unsigned i{pos - 1}; i < pol.n; i++)
            pol.Puntos.at(i) = pol.Puntos.at(i + 1);
        pol.n--;
        return pol;
    }
};

Poligono &Set(Poligono &pol, const unsigned &pos, const Punto &a)
{
    pol.Puntos.at(pos - 1) = a;
    return pol;
}; */

// Poligono &Remove2(Poligono &, const Punto &){};

