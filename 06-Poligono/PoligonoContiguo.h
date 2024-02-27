
#include <iostream>
#include <array>
#include "Punto.h"        //importa (depende de)
#include "FuncionesAux.h" //importa (depende de)

/***********************   Conjunto de valores     *********************/

struct PoligonoContiguo
{
    std::array<Punto, 100> Puntos;
    unsigned n;
};

/***********************   Declaracion del conjunto de Operaciones    *********************/

double Perimetro(const PoligonoContiguo &);
unsigned CantidadDeLados(const PoligonoContiguo &);
bool EstanSolapados(const PoligonoContiguo &, const PoligonoContiguo &);
bool EstaPuntoDentroDePoligonoContiguo(const Punto &a, const PoligonoContiguo &pol);
PoligonoContiguo &Push(PoligonoContiguo &, const Punto &);
Punto Pop(PoligonoContiguo &);
PoligonoContiguo &Pop2(PoligonoContiguo &);
Punto Top(const PoligonoContiguo &);
void Add(PoligonoContiguo &, const Punto &, const unsigned &);
PoligonoContiguo &Remove(PoligonoContiguo &, const unsigned &);
PoligonoContiguo &Remove2(PoligonoContiguo &, const Punto &);
Punto Get(const PoligonoContiguo &, const unsigned &);
PoligonoContiguo &Set(PoligonoContiguo &, const unsigned &, const Punto &);
PoligonoContiguo &Set2(PoligonoContiguo &, const Punto &, const Punto &);
unsigned Pos(const PoligonoContiguo &, const Punto &);
void DibujarPoligonos(const PoligonoContiguo &, const PoligonoContiguo &);

/****************  Implementacion del conjunto de Operaciones de PoligonoContiguo   *********************/

// Perimetro: PoligonoContiguo -> R
double Perimetro(const PoligonoContiguo &pol)
{
    double perimetro{};
    for (unsigned i{}; i < pol.n - 1; i++)
    {
        perimetro += GetDistancia(pol.Puntos.at(i), pol.Puntos.at(i + 1));
    }
    perimetro += GetDistancia(pol.Puntos.at(pol.n - 1), pol.Puntos.at(0));
    return perimetro;
}

// cantidad de lados: PoligonoContiguo -> N
unsigned CantidadDeLados(const PoligonoContiguo &Pol)
{
    return Pol.n;
}

// Esan Solapados: PoligonoContiguo X PoligonoContiguo -> bool
bool EstanSolapados(const PoligonoContiguo &pol1, const PoligonoContiguo &pol2)
{
    // Itero sobre los puntos del primer polígono
    for (unsigned i{}; i < pol2.n; i++)
    {
        // Verificar si el punto está dentro del segundo polígono
        if (EstaPuntoDentroDePoligonoContiguo(pol2.Puntos.at(i), pol1))
        {
            return true; // Al menos un vértice de PoligonoContiguo2 está dentro de PoligonoContiguo1
        }
    }
    // Itero sobre los puntos del segundo polígono
    for (unsigned i{}; i < pol1.n; i++)
    {
        if (EstaPuntoDentroDePoligonoContiguo(pol1.Puntos.at(i), pol2))
        {
            return true; // Al menos un vértice de PoligonoContiguo1 está dentro de PoligonoContiguo2
        }
    }
    return false; // Ningún vértice está dentro del otro polígono
}

// algortimo "ray casting" para saber si un punto pertenece a un PoligonoContiguo.
bool EstaPuntoDentroDePoligonoContiguo(const Punto &a, const PoligonoContiguo &pol)
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

// push: PoligonoContiguo X Punto -> PoligonoContiguo - Por composicion de funciones fluida
PoligonoContiguo &Push(PoligonoContiguo &Pol, const Punto &a)
{
    Pol.Puntos.at(Pol.n) = a;
    Pol.n++;
    return Pol;
}

// pop: PoligonoContiguo -> PoligonoContiguo x Punto
Punto Pop(PoligonoContiguo &pol)
{

    Punto puntoExtraido = Top(pol);

    pol.n--;

    return puntoExtraido;
}

// pop2: PoligonoContiguo -> PoligonoContiguo - por composidicon de funciones fluida
PoligonoContiguo &Pop2(PoligonoContiguo &Pol)
{
    Pol.n--;
    return Pol;
}

// Top: PoligonoContiguo -> Punto
Punto Top(const PoligonoContiguo &Pol)
{
    return Pol.Puntos.at(Pol.n - 1);
}

// Add: PoligonoContiguo X Punto X N -> PoligonoContiguo
void Add(PoligonoContiguo &pol, const Punto &a, const unsigned &pos)
{
    if (pos >= pol.n) // hago un push al final del array si quiero poner el punto en la ultima posicion o en una posicion superior
    {
        Push(pol, a);
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
}

// Remove: PoligonoContiguo X N -> PoligonoContiguo
PoligonoContiguo &Remove(PoligonoContiguo &pol, const unsigned &pos)
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

// PoligonoContiguo &Remove2(PoligonoContiguo &, const Punto &); - FALTA
PoligonoContiguo &Remove2(PoligonoContiguo &pol, const Punto &p)
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

// Get: PoligonoContiguo X N -> Punto
Punto Get(const PoligonoContiguo &Pol, const unsigned &pos)
{
    return Pol.Puntos.at(pos - 1);
}

// Set: PoligonoContiguo X N X Punto -> PoligonoContiguo
PoligonoContiguo &Set(PoligonoContiguo &pol, const unsigned &pos, const Punto &a)
{
    pol.Puntos.at(pos - 1) = a;
    return pol;
}

// Set2: PoligonoContiguo X Punto X Punto -> PoligonoContiguo - FALTA
PoligonoContiguo &Set2(PoligonoContiguo &pol, const Punto &p1, const Punto &p2)
{

    unsigned posPunto = Pos(pol, p1);
    pol.Puntos.at(posPunto - 1) = p2; // va el -1 ?
    return pol;
}

// Pos: PoligonoContiguo X Punto -> N
unsigned Pos(const PoligonoContiguo &pol, const Punto &a)
{
    for (unsigned i{}; i < pol.n; i++)
        if (SonIguales(a, pol.Puntos.at(i)))
            return i + 1;
    return pol.n;
}
void DibujarPoligonos(const PoligonoContiguo &pol1, const PoligonoContiguo &pol2)
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

