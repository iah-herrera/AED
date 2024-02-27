/*
    PoligonoContiguo.cpp
    TP06 Poligono
    Grupo 12
    Representacion de un poligono con una lista contigua.
*/

#include <iostream>
#include <cassert>
#include <array>
#include <cmath>

using std::array;

/***********************   Declaracion de estructuras     *********************/

struct Punto
{
    double x, y;
};

struct Poligono
{
    array<Punto, 100> Puntos;
    unsigned n;
};

/***********************   Declaracion de Funciones     *********************/

double GetDistancia(const Punto &, const Punto &);

// Perimetro: Poligono -> R
double Perimetro(const Poligono &);

// cantidad de lados: Poligono -> N
unsigned CantidadDeLados(const Poligono &);

// Esan Solapados: poligono X poligono -> bool (no es obligatorio)
bool EstanSolapados(const Poligono &pol1, const Poligono &pol2);

// algortimo "ray casting" para saber si un punto pertenece a un poligono.
bool EstaPuntoDentroDePoligono(const Punto &a, const Poligono &pol);

// push: Poligono X Punto -> Poligono - Por composicion de funciones fluida
Poligono &Push(Poligono &, const Punto &);

// pop: Poligono -> Poligono x Punto
Punto Pop(Poligono &);

// pop2: Poligono -> Poligono - por composidicon de funciones fluida
Poligono &Pop2(Poligono &);

// Top: Poligono -> Punto
Punto Top(const Poligono &);

// Add: Poligono X Punto X N -> Poligono
Poligono &Add(Poligono &, const Punto &, const unsigned &);

// Remove: Poligono X N -> Poligono
Poligono &Remove(Poligono &, const unsigned &);

// Remove2: Poligono X Punto -> Poligono
Poligono &Remove2(Poligono &, const Punto &);

// Get: Poligono X N -> Punto
Punto Get(const Poligono &, const unsigned &);

// Set: Poligono X N X Punto -> Poligono
Poligono &Set(Poligono &, const unsigned &, const Punto &);

// Set2: Poligono X Punto X Punto -> Poligono
Poligono &Set2(Poligono &pol, const Punto &p1, const Punto &p2);

// Pos: Poligono X Punto -> N
unsigned Pos(const Poligono &, const Punto &);

// Son Iguales: Punto X Punto -> B - Se desarrolla para verificar si dos puntos son iguales
bool SonIguales(const Punto &, const Punto &);
// Para poder comparar variables del tipo double - utiliza en SonIguales
bool AreNear(const double &, const double &, double = 0.0001);

void DibujarPoligonos(const Poligono &, const Poligono &);

/*********************      Main         *************************/

int main()
{
    Poligono p{};
    Poligono p1{};
    Poligono p2{};
    Push(Push(Push(p, {5, 8}), {3.4, 8.4}), {5.5, 6.7}); // {5, 8},{3.4, 8.4},{5.5, 6.7}
    assert(AreNear(Perimetro(p), 5.7439));
    Punto a{5.5, 6.7};
    assert(CantidadDeLados(p) == 3);
    assert(SonIguales(a, Top(p)));
    Add(p, {8, 8}, 2);                     // {5, 8},{8,8},{3.4, 8.4},{5.5, 6.7}
    Add(p, {6.8, 8.7}, 50);                // {5, 8},{8,8},{3.4, 8.4},{5.5, 6.7},{6.8, 8.7}
    assert(CantidadDeLados(Pop2(p)) == 4); // {5, 8},{8,8},{3.4, 8.4},{5.5, 6.7}
    assert(Pos(p, {8, 8}) == 2);
    assert(SonIguales({5.5, 6.7}, Get(p, 4)));
    assert(SonIguales({3.4, 8.4}, Get(p, 3)));
    Remove(p, 3);                              // {5, 8},{8,8},{5.5, 6.7}
    assert(SonIguales({5.5, 6.7}, Get(p, 3))); //
    Set(p, 1, {0.5, 3.8});                     // {0.5, 3.8},{8,8},{5.5, 6.7}
    assert(SonIguales({0.5, 3.8}, Get(p, 1))); //
    Set2(p, {5.5, 6.7}, {2, 2});               // {0.5, 3.8},{8,8},{2, 2}
    assert(SonIguales({2, 2}, Get(p, 3)));     //
    Remove2(p, {0.5, 3.8});                    // {8,8},{2, 2}
    assert(SonIguales({2, 2}, Get(p, 2)));     //
    Push(Push(p, {2, 3}), {7, 1.6});           // p=(8,8),(2,2),(2,3),(7,1.6)
    assert(CantidadDeLados(p) == 4);
    Pop(p);
    assert(CantidadDeLados(p) == 3);

    // armo dos nuevos poligonos y pruebo si estan solapados
    Push(Push(Push(Push(p1, {850, 75}), {850, 200}), {200, 200}), {200, 75});
    Push(Push(Push(Push(Push(Push(p2, {850, 75}), {958, 137.5}), {958, 262.5}), {850, 325}), {742, 262.6}), {742, 137.5});

    assert(EstanSolapados(p1, p2));
    DibujarPoligonos(p1, p2);
}

/*********************      Definicion de Funciones       *************************/

double GetDistancia(const Punto &p1, const Punto &p2)
{
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

// Perimetro: Poligono -> R
double Perimetro(const Poligono &pol)
{
    double perimetro{};
    for (unsigned i{}; i < pol.n - 1; i++)
    {
        perimetro += GetDistancia(pol.Puntos.at(i), pol.Puntos.at(i + 1));
    }
    perimetro += GetDistancia(pol.Puntos.at(pol.n - 1), pol.Puntos.at(0));
    return perimetro;
}

// cantidad de lados: Poligono -> N
unsigned CantidadDeLados(const Poligono &Pol)
{
    return Pol.n;
}

// Esan Solapados: poligono X poligono -> bool
bool EstanSolapados(const Poligono &pol1, const Poligono &pol2)
{
    // Itero sobre los puntos del primer polígono
    for (unsigned i{}; i < pol2.n; i++)
    {
        // Verificar si el punto está dentro del segundo polígono
        if (EstaPuntoDentroDePoligono(pol2.Puntos.at(i), pol1))
        {
            return true; // Al menos un vértice de poligono2 está dentro de poligono1
        }
    }
    // Itero sobre los puntos del segundo polígono
    for (unsigned i{}; i < pol1.n; i++)
    {
        if (EstaPuntoDentroDePoligono(pol1.Puntos.at(i), pol2))
        {
            return true; // Al menos un vértice de poligono1 está dentro de poligono2
        }
    }
    return false; // Ningún vértice está dentro del otro polígono
}

// algortimo "ray casting" para saber si un punto pertenece a un poligono.
bool EstaPuntoDentroDePoligono(const Punto &a, const Poligono &pol)
{
    int cruces = 0;
    // Itero sobre los lados del polígono
    for (unsigned i{}; i < pol.n; i++)
    {
        const Punto &v1 = pol.Puntos.at(i);
        const Punto &v2 = pol.Puntos.at((i + 1));
        // Comprobar si el rayo cruza la arista
        if ((v1.y > a.y) != (v2.y > a.y) && a.x < (v2.x - v1.x) * (a.y - v1.y) / (v2.y - v1.y) + v1.x)
        {
            cruces++;
        }
    }
    return (cruces % 2 == 1); // Devolver true si el número de cruces es impar
}

// push: Poligono X Punto -> Poligono - Por composicion de funciones fluida
Poligono &Push(Poligono &Pol, const Punto &a)
{
    Pol.Puntos.at(Pol.n) = a;
    Pol.n++;
    return Pol;
}

// pop: Poligono -> Poligono x Punto
Punto Pop(Poligono &pol)
{
    if (pol.n == 0)
        return {0.0, 0.0}; // si el polinomio esta vacio retorno el origen
    Punto puntoExtraido = Top(pol);

    pol.n--;

    return puntoExtraido;
}

// pop2: Poligono -> Poligono - por composidicon de funciones fluida
Poligono &Pop2(Poligono &Pol)
{
    if (Pol.n == 0) // si el polinomio esta vacio
        return Pol;
    Pol.n--;
    return Pol;
}

// Top: Poligono -> Punto
Punto Top(const Poligono &pol)
{
    if (pol.n == 0)
        return {0.0, 0.0}; // si el polinomio esta vacio retorno el punto al origen
    return pol.Puntos.at(pol.n - 1);
}

// Add: Poligono X Punto X N -> Poligono
Poligono &Add(Poligono &pol, const Punto &a, const unsigned &pos)
{
    if (pos > pol.n) // hago un push al final del array si quiero poner el punto en la ultima posicion o en una posicion superior
    {
        Push(pol, a);
        return pol;
    }
    else
    {
        for (unsigned i{pol.n}; i >= pos; i--)
        {
            pol.Puntos.at(i) = pol.Puntos.at(i - 1);
        }
        pol.Puntos.at(pos - 1) = a;
        pol.n++;
        return pol;
    }
}

// Remove: Poligono X N -> Poligono
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
}

// Remove2: Poligono X Punto -> Poligono
Poligono &Remove2(Poligono &pol, const Punto &p)
{

    unsigned posPunto = Pos(pol, p);

    if (posPunto > pol.n)
        return pol;
    else
    {
        for (unsigned i{posPunto - 1}; i < pol.n; i++)
            pol.Puntos.at(i) = pol.Puntos.at(i + 1);
        pol.n--;
        return pol;
    }
}

// Get: Poligono X N -> Punto
Punto Get(const Poligono &Pol, const unsigned &pos)
{
    return Pol.Puntos.at(pos - 1);
}

// Set: Poligono X N X Punto -> Poligono
Poligono &Set(Poligono &pol, const unsigned &pos, const Punto &a)
{
    pol.Puntos.at(pos - 1) = a;
    return pol;
}

// Set2: Poligono X Punto X Punto -> Poligono
Poligono &Set2(Poligono &pol, const Punto &p1, const Punto &p2)
{

    unsigned posPunto = Pos(pol, p1);
    pol.Puntos.at(posPunto - 1) = p2;
    return pol;
}

// Pos: Poligono X Punto -> N
unsigned Pos(const Poligono &pol, const Punto &a)
{
    for (unsigned i{}; i < pol.n; i++)
        if (SonIguales(a, pol.Puntos.at(i)))
            return i + 1;
    return pol.n;
}

// Son Iguales: Punto X Punto -> B - Se desarrolla para verificar si dos puntos son iguales
bool SonIguales(const Punto &a, const Punto &b)
{
    if (AreNear(a.x, b.x) and AreNear(a.y, b.y))
        return true;
    else
        return false;
}

// Para poder comparar variables del tipo double - se utiliza en SonIguales
bool AreNear(const double &a, const double &b, double tolerancia)
{
    return (a - tolerancia) <= b and b <= (a + tolerancia);
}

void DibujarPoligonos(const Poligono &pol1, const Poligono &pol2)
{
    std::cout << "<svg width=\"24cm\" height=\"8cm\" viewBox=\"0 0 1200 400\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << '\n';
    std::cout << "<polygon fill=\"#b2dafa\" stroke=\"#252440\" stroke-width=\"10\" points=\"";
    for (unsigned i{}; i < pol1.n; i++)
    {
        std::cout << pol1.Puntos.at(i).x << "," << pol1.Puntos.at(i).y << " ";
    }
    std::cout << "\" />\n";
    std::cout << "<polygon fill=\"#ffe3e8\" stroke=\"#5d2417\" stroke-width=\"10\" points=\"";
    for (unsigned i{}; i < pol2.n; i++)
    {
        std::cout << pol2.Puntos.at(i).x << "," << pol2.Puntos.at(i).y << " ";
    }
    std::cout << "\" />\n</svg>\n";
}
