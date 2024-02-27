/*
    PoligonoEnlazada.cpp
    TP06 Poligono
    Grupo 12
    Representacion de un poligono con una lista enlazada.
*/

#include <iostream>
#include <cassert>
#include <array>
#include <cmath>

/***********************   Declaracion de estructuras     *********************/

struct Punto
{
    double x, y;
};

struct Nodo
{
    Punto puntos;
    Nodo *next{nullptr};
};

struct Poligono
{
    Nodo *primero{nullptr};
};

/***********************   Declaracion de Funciones     *********************/

double GetDistancia(const Punto &, const Punto &);

// Perimetro: Poligono -> R
double Perimetro(const Poligono &);

// cantidad de lados: Poligono -> N
unsigned CantidadDeLados(const Poligono &);

// Estan Solapados: poligono X poligono -> bool (no es obligatorio)
bool EstanSolapados(const Poligono &pol1, const Poligono &pol2);

// algortimo "ray casting" para saber si un punto pertenece a un poligono.
bool EstaPuntoDentroDePoligono(const Punto &a, const Poligono &pol);

// push: Poligono X Punto -> Poligono - Por composicion de funciones fluida
Poligono &Push(Poligono &, const Punto &);

// pop: Poligono -> Poligono x Punto
Punto Pop(Poligono &pol);

// pop2: Poligono -> Poligono - por composidicon de funciones fluida
Poligono &Pop2(Poligono &);

// Top: Poligono -> Punto
Punto Top(const Poligono &);

// Add: Poligono X Punto X N -> Poligono
Poligono &Add(Poligono &, const Punto &, const unsigned &);

// Remove: Poligono X N -> Poligono
Poligono &Remove(Poligono &, const unsigned &);

// Remove2: Poligono X Punto -> Poligono
Poligono &Remove2(Poligono &pol, const Punto &a);

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

// Para dibujar los poligonos solapados
void DibujarPoligonos(const Poligono &pol1, const Poligono &pol2);

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

    Push(Push(Push(Push(p1, {100, 100}), {100, 200}), {200, 200}), {200, 100}); // p1 = {1, 1},{1, 2}, {2, 2}, {2, 1}
    Push(Push(Push(Push(p2, {150, 150}), {150, 250}), {250, 250}), {250, 150}); // p2 = {1.5, 1.5}, {1.5, 2.5}, {2.5, 2.5}, {2.5, 1.5}
    assert(EstanSolapados(p1, p2));
    DibujarPoligonos(p1, p2);
};

/*********************      Definicion de Funciones       *************************/

double GetDistancia(const Punto &p1, const Punto &p2)
{
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

// Perimetro: Poligono -> R
double Perimetro(const Poligono &pol)
{
    if (pol.primero == nullptr || pol.primero->next == nullptr)
    {
        // si la lista esta vacía o tiene un solo punto, el perímetro = 0
        return 0.0;
    }
    double perimetro{};
    auto actual{pol.primero};
    for (; actual->next; actual = actual->next)
    {
        perimetro += GetDistancia(actual->puntos, actual->next->puntos);
    }
    perimetro += GetDistancia(actual->puntos, pol.primero->puntos); // calcula distancia entre ultimo punto y primero

    return perimetro;
}

// cantidad de lados: Poligono -> N
unsigned CantidadDeLados(const Poligono &pol)
{
    unsigned i{};
    for (auto actual{pol.primero}; actual; actual = actual->next)
        i++;
    return i;
}

// Estan Solapados: poligono X poligono -> bool (no es obligatorio)
bool EstanSolapados(const Poligono &pol1, const Poligono &pol2)
{
    // Itero sobre los puntos del primer polígono
    for (auto actual{pol1.primero}; actual; actual = actual->next)
    {
        // Verificar si el punto está dentro del segundo polígono
        if (EstaPuntoDentroDePoligono(actual->puntos, pol2))
        {
            return true; // Al menos un vértice de poligono1 está dentro de poligono2
        }
    }
    // Itero sobre los puntos del segundo polígono
    for (auto actual{pol2.primero}; actual; actual = actual->next)
    {
        // Verificar si el punto está dentro del primer polígono
        if (EstaPuntoDentroDePoligono(actual->puntos, pol1))
        {
            return true; // Al menos un vértice de poligono2 está dentro de poligono1
        }
    }

    return false; // Ningún punto está dentro del otro polígono
}

// algortimo "ray casting" para saber si un punto pertenece a un poligono.
bool EstaPuntoDentroDePoligono(const Punto &a, const Poligono &pol)
{
    int cruces = 0;
    auto actual{pol.primero};
    // Itero sobre los lados del polígono
    for (; actual; actual = actual->next)
    {
        const Punto &v1 = actual->puntos;
        const Punto &v2 = actual->next->puntos;
        // Comprobar si el rayo cruza la arista
        if ((v1.y > a.y) != (v2.y > a.y) && a.x < (v2.x - v1.x) * (a.y - v1.y) / (v2.y - v1.y) + v1.x)
        {
            cruces++;
        }
        actual = actual->next;
    }
    return (cruces % 2 == 1); // Devolver true si el número de cruces es impar
}

// push: Poligono X Punto -> Poligono - Por composicion de funciones fluida
Poligono &Push(Poligono &pol, const Punto &a)
{

    if (pol.primero == nullptr)
    {
        pol.primero = new Nodo{a};
        return pol;
    }
    auto actual{pol.primero};
    for (; actual->next; actual = actual->next)
    {
    }
    actual->next = new Nodo{a};
    return pol;
}

// pop: Poligono -> Poligono x Punto
Punto Pop(Poligono &pol)
{

    if (pol.primero == nullptr)
        return {0.0, 0.0};

    if (pol.primero->next == nullptr)
    {
        Punto puntoEliminado = Top(pol);
        delete pol.primero;
        pol.primero = {nullptr};
        return puntoEliminado;
    }
    auto actual{pol.primero};
    for (; actual->next->next; actual = actual->next)
    {
    }
    Punto puntoEliminado = Top(pol);
    delete actual->next;
    actual->next = nullptr;
    return puntoEliminado;
}

// pop2: Poligono -> Poligono - por composidicon de funciones fluida
Poligono &Pop2(Poligono &pol)
{
    if (pol.primero == nullptr) // Verifico que la lista no este vacia.
        return pol;
    if (pol.primero->next == nullptr) // Cubro el caso en el que la lista solo tiene un nodo.
    {
        delete pol.primero;
        pol.primero = {nullptr};
        return pol;
    }
    auto actual{pol.primero};
    for (; actual->next->next; actual = actual->next) // recorro la lista hasta el anteultimo nudo
    {
    }
    delete actual->next;    // libero la reserva del ultimo nodo
    actual->next = nullptr; // el nodo actual termina sienod el ultimo

    return pol;
}

// Top: Poligono -> Punto
Punto Top(const Poligono &pol)
{
    if (pol.primero == nullptr) // lista vacia entonces retorno el punto al origen
        return {0.0, 0.0};
    auto actual{pol.primero};
    for (; actual->next; actual = actual->next) // recorro list para devolver ultimo punto
    {
    }
    return actual->puntos;
}

// Add: Poligono X Punto X N -> Poligono
Poligono &Add(Poligono &pol, const Punto &a, const unsigned &pos)
{
    if (pol.primero == nullptr) // lista vacia
    {
        pol.primero = new Nodo{a};
        return pol;
    }
    if (pos <= 1) // add a la primera posicion
    {
        pol.primero = new Nodo{a, pol.primero};
        return pol;
    }
    if (pos > CantidadDeLados(pol)) // mayor a la cantidad de lados
    {
        Push(pol, a); // lo meto al final de la lista, me sube una orden de magnitud.
        return pol;
    }
    auto actual{pol.primero};
    for (unsigned i{2}; i < pos; i++) // insert despues del principio
        actual = actual->next;
    actual->next = new Nodo{a, actual->next};
    return pol;
}

// Remove: Poligono X N -> Poligono
Poligono &Remove(Poligono &pol, const unsigned &pos)
{
    if (pol.primero == nullptr)
        return pol;

    if (pos <= 1)
    {
        auto NodoAEliminar = pol.primero;
        pol.primero = pol.primero->next;
        delete NodoAEliminar;
        return pol;
    }

    unsigned i{1};
    auto actual{pol.primero};
    for (; i < pos - 1; i++)
    {
        actual = actual->next;
    }

    auto NodoAEliminar = actual->next;
    actual->next = actual->next->next;
    delete NodoAEliminar;
    return pol;
}

// Remove2: Poligono X Punto -> Poligono
Poligono &Remove2(Poligono &pol, const Punto &a)
{
    if (pol.primero == nullptr) // Verifico que la lista no este vacia.
        return pol;
    auto NodoAEliminar{pol.primero};
    if (SonIguales(pol.primero->puntos, a)) // Cubro el caso de querer sacar el punto del primer nodo.
    {
        auto NodoAEliminar = pol.primero;
        pol.primero = pol.primero->next;
        delete NodoAEliminar;
        return pol;
    }
    auto actual{pol.primero}; // recorro el polinomio par ael reso de los casos.
    for (; actual->next; actual = actual->next)
    {
        if (SonIguales(actual->next->puntos, a))
        {
            NodoAEliminar = actual->next;
            actual->next = actual->next->next;
            delete NodoAEliminar;
            return pol;
        }
    }
    return pol; // si no existe ese punto retorno pol
}

// Get: Poligono X N -> Punto
Punto Get(const Poligono &pol, const unsigned &pos)
{

    auto actual{pol.primero};
    for (unsigned i{1}; i < pos; i++)
        actual = actual->next;
    return actual->puntos;
}

// Set: Poligono X N X Punto -> Poligono
Poligono &Set(Poligono &pol, const unsigned &pos, const Punto &a)
{
    if (pol.primero == nullptr || pos > CantidadDeLados(pol))
        return pol;

    if (pos <= 1)
    {
        pol.primero->puntos = a;
        return pol;
    }
    auto actual{pol.primero};
    for (unsigned i{1}; i < pos; i++)
        actual = actual->next;
    actual->puntos = a;
    return pol;
}

// Set2: Poligono X Punto X Punto -> Poligono
Poligono &Set2(Poligono &pol, const Punto &p1, const Punto &p2) // p1 es el actual, p2 es el nuevo
{
    if (pol.primero == nullptr) // Verifico que la lista no este vacia.
        return pol;
    auto actual{pol.primero};
    for (; actual; actual = actual->next)
    {
        if (SonIguales(actual->puntos, p1))
        {
            actual->puntos = p2;
            return pol;
        }
    }
    return pol;
}

// Pos: Poligono X Punto -> N
unsigned Pos(const Poligono &pol, const Punto &a)
{
    unsigned i{1};
    for (auto actual{pol.primero}; actual; actual = actual->next)
    {
        if (SonIguales(actual->puntos, a))
            return i;
        i++;
    }
    return i;
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

// Para dibujar los poligonos solapados
void DibujarPoligonos(const Poligono &pol1, const Poligono &pol2)
{
    std::cout << "<svg width=\"24cm\" height=\"8cm\" viewBox=\"0 0 1200 400\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << '\n';
    std::cout << "<polygon fill=\"#b2dafa\" stroke=\"#252440\" stroke-width=\"5\" points=\"";
    for (auto actual{pol1.primero}; actual; actual = actual->next)
    {
        std::cout << actual->puntos.x << "," << actual->puntos.y << " ";
    }
    std::cout << "\" />\n";
    std::cout << "<polygon fill=\"#ffe3e8\" stroke=\"#5d2417\" stroke-width=\"5\" points=\"";
    for (auto actual{pol2.primero}; actual; actual = actual->next)
    {
        std::cout << actual->puntos.x << "," << actual->puntos.y << " ";
    }
    std::cout << "\" />\n</svg>\n";
}