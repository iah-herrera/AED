
#include <iostream>
#include "Punto.h"        //importa (depende de)
#include "FuncionesAux.h" //importa (depende de)

/***********************   Conjunto de valores     *********************/

struct Nodo
{
    Punto puntos;
    Nodo *next{nullptr};
};

struct PoligonoEnlazado
{
    Nodo *primero{nullptr};
};

/***********************   Declaracion del conjunto de Operaciones    *********************/

double GetDistancia(const Punto &, const Punto &);
double Perimetro(const PoligonoEnlazado &);
unsigned CantidadDeLados(const PoligonoEnlazado &);
bool EstanSolapados(const PoligonoEnlazado &pol1, const PoligonoEnlazado &pol2);
bool EstaPuntoDentroDePoligonoEnlazado(const Punto &a, const PoligonoEnlazado &pol);
PoligonoEnlazado &Push(PoligonoEnlazado &, const Punto &);
Punto Pop(PoligonoEnlazado &pol);
PoligonoEnlazado &Pop2(PoligonoEnlazado &);
Punto Top(const PoligonoEnlazado &);
PoligonoEnlazado &Add(PoligonoEnlazado &, const Punto &, const unsigned &);
PoligonoEnlazado &Remove(PoligonoEnlazado &, const unsigned &);
PoligonoEnlazado &Remove2(PoligonoEnlazado &pol, const Punto &a);
Punto Get(const PoligonoEnlazado &, const unsigned &);
PoligonoEnlazado &Set(PoligonoEnlazado &, const unsigned &, const Punto &);
PoligonoEnlazado &Set2(PoligonoEnlazado &pol, const Punto &p1, const Punto &p2);
unsigned Pos(const PoligonoEnlazado &, const Punto &);
void DibujarPoligonos(const PoligonoEnlazado &pol1, const PoligonoEnlazado &pol2);

/****************  Implementacion del conjunto de Operaciones de PoligonoEnlazado   *********************/

// Perimetro: PoligonoEnlazado -> R
double Perimetro(const PoligonoEnlazado &pol)
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

// Cantidad de lados: PoligonoEnlazado -> N
unsigned CantidadDeLados(const PoligonoEnlazado &pol)
{
    unsigned i{};
    for (auto actual{pol.primero}; actual; actual = actual->next)
        i++;
    return i;
}

// Esan Solapados: PoligonoEnlazado X PoligonoEnlazado -> bool
bool EstanSolapados(const PoligonoEnlazado &pol1, const PoligonoEnlazado &pol2)
{
    // Itero sobre los puntos del primer polígono
    for (auto actual{pol1.primero}; actual; actual = actual->next)
    {
        // Verificar si el punto está dentro del segundo polígono
        if (EstaPuntoDentroDePoligonoEnlazado(actual->puntos, pol2))
        {
            return true; // Al menos un vértice de PoligonoEnlazado1 está dentro de PoligonoEnlazado2
        }
    }
    // Itero sobre los puntos del segundo polígono
    for (auto actual{pol2.primero}; actual; actual = actual->next)
    {
        // Verificar si el punto está dentro del primer polígono
        if (EstaPuntoDentroDePoligonoEnlazado(actual->puntos, pol1))
        {
            return true; // Al menos un vértice de PoligonoEnlazado2 está dentro de PoligonoEnlazado1
        }
    }

    return false; // Ningún punto está dentro del otro polígono
}

// algortimo "ray casting" para saber si un punto pertenece a un PoligonoEnlazado.
bool EstaPuntoDentroDePoligonoEnlazado(const Punto &a, const PoligonoEnlazado &pol)
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

// push: PoligonoEnlazado X Punto -> PoligonoEnlazado - Por composicion de funciones fluida
PoligonoEnlazado &Push(PoligonoEnlazado &pol, const Punto &a)
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

// pop: PoligonoEnlazado -> PoligonoEnlazado x Punto
Punto Pop(PoligonoEnlazado &pol)
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

// pop2: PoligonoEnlazado -> PoligonoEnlazado - por composidicon de funciones fluida
PoligonoEnlazado &Pop2(PoligonoEnlazado &pol)
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

// Top: PoligonoEnlazado -> Punto
Punto Top(const PoligonoEnlazado &pol)
{
    if (pol.primero == nullptr) // lista vacia entonces retorno el punto al origen
        return {0.0, 0.0};
    auto actual{pol.primero};
    for (; actual->next; actual = actual->next) // recorro list para devolver ultimo punto
    {
    }
    return actual->puntos;
}

// Add: PoligonoEnlazado X Punto X N -> PoligonoEnlazado
PoligonoEnlazado &Add(PoligonoEnlazado &pol, const Punto &a, const unsigned &pos)
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

// Remove: PoligonoEnlazado X N -> PoligonoEnlazado
PoligonoEnlazado &Remove(PoligonoEnlazado &pol, const unsigned &pos)
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

// Remove2: PoligonoEnlazado X Punto -> PoligonoEnlazado
PoligonoEnlazado &Remove2(PoligonoEnlazado &pol, const Punto &a)
{

    unsigned PosPunto = Pos(pol, a);

    auto actual{pol.primero};
    if (PosPunto <= 1)
    {
        auto *nodoAEliminar = pol.primero;
        pol.primero = pol.primero->next;
        delete nodoAEliminar;
        return pol;
    }

    for (unsigned i{1}; i < PosPunto - 1; i++)
        actual = actual->next;

    auto NodoAEliminar = actual->next;
    actual->next = actual->next->next;
    delete NodoAEliminar;
    return pol;
}

// Get: PoligonoEnlazado X N -> Punto
Punto Get(const PoligonoEnlazado &pol, const unsigned &pos)
{

    auto actual{pol.primero};
    for (unsigned i{1}; i < pos; i++)
        actual = actual->next;
    return actual->puntos;
}

// Set: PoligonoEnlazado X N X Punto -> PoligonoEnlazado
PoligonoEnlazado &Set(PoligonoEnlazado &pol, const unsigned &pos, const Punto &a)
{
    if (pol.primero == nullptr || pos > CantidadDeLados(pol)) // lista vacia
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

// Set2: PoligonoEnlazado X Punto X Punto -> PoligonoEnlazado
PoligonoEnlazado &Set2(PoligonoEnlazado &pol, const Punto &a, const Punto &b)
{

    unsigned PosPunto = Pos(pol, a);

    auto actual{pol.primero};
    for (unsigned i{1}; i < PosPunto; i++) // insert despues del principio
        actual = actual->next;
    actual->puntos = b;
    return pol;
}

// Pos: PoligonoEnlazado X Punto -> N
unsigned Pos(const PoligonoEnlazado &pol, const Punto &a)
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

// Para dibujar los poligonos solapados
void DibujarPoligonos(const PoligonoEnlazado &pol1, const PoligonoEnlazado &pol2)
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