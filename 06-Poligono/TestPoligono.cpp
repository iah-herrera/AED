/*
    TestPoligono.cpp
    TP06 Poligono
    Grupo 12
    Representacion de un poligono con una lista contigua y enlazada
*/

// #include <iostream>
#include <cassert>
#include "Punto.h"            //importa (depende de)
#include "FuncionesAux.h"     //importa (depende de)
#include "PoligonoContiguo.h" //importa (depende de)
#include "PoligonoEnlazado.h" //importa (depende de)

static PoligonoContiguo pc{};
static PoligonoEnlazado pe{};

// Este main depende de : Punto, cassert, funcionesAux.
int main()
{

    // Pruebas de poligono contiguo

    Push(Push(Push(pc, {5, 8}), {3.4, 8.4}), {5.5, 6.7}); // {5, 8},{3.4, 8.4},{5.5, 6.7}
    assert(AreNear(Perimetro(pc), 5.7439));
    Punto a{5.5, 6.7};
    assert(CantidadDeLados(pc) == 3);
    assert(SonIguales(a, Top(pc)));
    Add(pc, {8, 8}, 2);                     // {5, 8},{8,8},{3.4, 8.4},{5.5, 6.7}
    Add(pc, {6.8, 8.7}, 50);                // {5, 8},{8,8},{3.4, 8.4},{5.5, 6.7},{6.8, 8.7}
    assert(CantidadDeLados(Pop2(pc)) == 4); // {5, 8},{8,8},{3.4, 8.4},{5.5, 6.7}
    assert(Pos(pc, {8, 8}) == 2);
    assert(SonIguales({5.5, 6.7}, Get(pc, 4)));
    assert(SonIguales({3.4, 8.4}, Get(pc, 3)));
    Remove(pc, 3);                              // {5, 8},{8,8},{5.5, 6.7}
    assert(SonIguales({5.5, 6.7}, Get(pc, 3))); //
    Set(pc, 1, {0.5, 3.8});                     // {0.5, 3.8},{8,8},{5.5, 6.7}
    assert(SonIguales({0.5, 3.8}, Get(pc, 1))); //
    Set2(pc, {5.5, 6.7}, {2, 2});               // {0.5, 3.8},{8,8},{2, 2}
    assert(SonIguales({2, 2}, Get(pc, 3)));     //
    Remove2(pc, {0.5, 3.8});                    // {8,8},{2, 2}
    assert(SonIguales({2, 2}, Get(pc, 2)));     //
    Push(Push(pc, {2, 3}), {7, 1.6});           // p=(8,8),(2,2),(2,3),(7,1.6)
    assert(CantidadDeLados(pc) == 4);
    Pop(pc);
    assert(CantidadDeLados(pc) == 3);

    // armo dos nuevos poligonos y pruebo si estan solapados
    PoligonoContiguo pc1{};
    PoligonoContiguo pc2{};

    Push(Push(Push(Push(pc1, {850, 75}), {850, 200}), {200, 200}), {200, 75});                                              // p1 = {1, 1},{1, 2}, {2, 2}, {2, 1}
    Push(Push(Push(Push(Push(Push(pc2, {850, 75}), {958, 137.5}), {958, 262.5}), {850, 325}), {742, 262.6}), {742, 137.5}); // p2 = {1.5, 1.5}, {1.5, 2.5}, {2.5, 2.5}, {2.5, 1.5}

    assert(EstanSolapados(pc1, pc2));
    DibujarPoligonos(pc1, pc2);

    // Pruebas de poligono enlazado

    Push(Push(Push(pe, {5, 8}), {3.4, 8.4}), {5.5, 6.7}); // {5, 8},{3.4, 8.4},{5.5, 6.7}
    assert(AreNear(Perimetro(pe), 5.7439));
    Punto b{5.5, 6.7};
    assert(CantidadDeLados(pe) == 3);
    assert(SonIguales(b, Top(pe)));
    Add(pe, {8, 8}, 2);                     // {5, 8},{8,8},{3.4, 8.4},{5.5, 6.7}
    Add(pe, {6.8, 8.7}, 50);                // {5, 8},{8,8},{3.4, 8.4},{5.5, 6.7},{6.8, 8.7}
    assert(CantidadDeLados(Pop2(pe)) == 4); // {5, 8},{8,8},{3.4, 8.4},{5.5, 6.7}
    assert(Pos(pe, {8, 8}) == 2);
    assert(SonIguales({5.5, 6.7}, Get(pe, 4)));
    assert(SonIguales({3.4, 8.4}, Get(pe, 3)));
    Remove(pe, 3);                              // {5, 8},{8,8},{5.5, 6.7}
    assert(SonIguales({5.5, 6.7}, Get(pe, 3))); //
    Set(pe, 1, {0.5, 3.8});                     // {0.5, 3.8},{8,8},{5.5, 6.7}
    assert(SonIguales({0.5, 3.8}, Get(pe, 1))); //
    Set2(pe, {5.5, 6.7}, {2, 2});               // {0.5, 3.8},{8,8},{2, 2}
    assert(SonIguales({2, 2}, Get(pe, 3)));     //
    Remove2(pe, {0.5, 3.8});                    // {8,8},{2, 2}
    assert(SonIguales({2, 2}, Get(pe, 2)));     //
    Push(Push(pe, {2, 3}), {7, 1.6});           // p=(8,8),(2,2),(2,3),(7,1.6)
    assert(CantidadDeLados(pe) == 4);
    Pop(pe);
    assert(CantidadDeLados(pe) == 3);

    // armo dos nuevos poligonos y pruebo si estan solapados
    PoligonoEnlazado pe1{};
    PoligonoEnlazado pe2{};

    Push(Push(Push(Push(pe1, {100, 100}), {100, 200}), {200, 200}), {200, 100}); // p1 = {1, 1},{1, 2}, {2, 2}, {2, 1}
    Push(Push(Push(Push(pe2, {150, 150}), {150, 250}), {250, 250}), {250, 150}); // p2 = {1.5, 1.5}, {1.5, 2.5}, {2.5, 2.5}, {2.5, 1.5}
    assert(EstanSolapados(pe1, pe2));
    DibujarPoligonos(pe1, pe2);
}
