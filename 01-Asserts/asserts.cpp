/*
    asserts.cpp
    TP01 Asserts
    Grupo 12
*/

#include <cassert>
#include <string>

using namespace std::literals;

int main()
{
    // Se probarán asserts con diferentes tipos de variables, buscando que no den error
    
    // -------------------- bool ----------------------

    assert(not true == false);          // Operador lógico not
    assert(true and true == true);      // Operador lógico and
    assert(false or false == false);    // Operador lógico and
    
    // ------------------------ char ---------------------------
    assert('A' == 65);       // Comparamos por igual y demostramos la equivalencia
    assert('A'+1 == 'B');    // Operador de suma
    assert('A'-1 == '@');    // Operador de resta
    assert('A'*2 == 130);    // Operador de multiplicacion
    assert('A'/2 == 32);     // Operdador de division
    assert('A'%2 == 1);      // Operador de resto
    assert('B' >= 'A');      // Operador de comparacion mayor o igual
    assert('A' <= 'B');      // Operador de comparacion menor o igual
    
    // -------------------- unsigned ----------------------

    assert(10u+1u == 11u);              // Operador de suma
    assert(10u-1u == 9u);               // Operador de resta
    assert(10u*2u == 20u);              // Operador de multiplicaciÃ³n
    assert(10u/2u == 5u);               // Operador de divisiÃ³n
    assert(11u%2 == 1);                 // Operador de resto
    assert(10u >= 8u);                  // Operador de comparaciÃ³n mayor o igual
    assert(10u <= 12u);                 // Operador de comparaciÃ³n menor o igual
    
    assert(0u-1u >= 0u); // Deberia dar error si pudiesemos colocar numeros negativos.

    /* 0-1 es -1, pero el tipo de datos unsigned no contiene el conjunto de numeros negativos.
    Como en este caso se le asigna 32 bits de memoria al tipo de datos unsigned, podemos representar
    numeros desde el 0 hasta el 4294967295 (2^32-1).
    Por otro lado, modificando el ultimo ejemplo se puede observar el comportamiento de la aseveracion
    quitando el sufijo u a los diferentes numeros.
    */
    
   // ----------------------- int -------------------------
    assert(10+1 == 11);                 // Operador de suma
    assert(10-1 == 9);                  // Operador de resta
    assert(10*2 == 20);                 // Operador de multiplicación
    assert(10/2 == 5);                  // Operador de división
    assert(5%2 == 1);                   // Operador de resto
    assert(10 >= 8);                    // Operador de comparación mayor o igual
    assert(10 <= 12);                   // Operador de comparación menor o igual
    
    assert(10 <= 12);                   // Operador de comparación menor o igual
    assert(0-1 < 0 and 0-1 == -1);      // Vemos la capacidad de utilizar números negativos
    assert(2*-1 == -2 and 2/-2 == -1);  // Jugamos con la notación para resaltar el NO uso de paréntesis
    assert(2147483647+1 <= 0); // Un número positivo más otro positivo no debería dar negativo D: ¿O sí?
   
    /*
        En una aseveración como la última: assert(2*-1 == -2 and 2/-2 == -1);
         - Primero tenemos una operación de multiplicación entre enteros que devuelve un entero
         - Segundo tenemos la división entre enteros que también devuelve un entero
         - Tercero tenemos la primera comparación por igual que compara enteros pero devuelve un bool
         - Cuarto tenemos la otra comparación por igual que también compara enteros y devuelve un bool
         - Quinto tenemos una operación lógica que es como tener true and true devolviéndonos true
    
    La última aclaración es que no utilizamos sufijos porque por defecto c++ utiliza el tipo de dato
    int si es que el número no tiene parte fraccionaria. De tenerla, pasaría a utilizar datos del tipo double
    */
    
    // --------------------- double ------------------------

    assert(10+0.5 == 10.5);             // Operador de suma
    assert(10-0.5 == 9.5);              // Operador de resta
    assert(4.5*2 == 9);                 // Operador de multiplicación
    assert(11.0/2.0 == 5.5);            // Operador de división
    assert(0.5 >= 0);                   // Operador de comparación mayor o igual
    assert(1.5 <= 2);                   // Operador de comparación menor o igual
    
    assert(0-0.5 < 0 and 0-0.5 == -0.5);      // Vemos la capacidad de utilizar números negativos

    // Notamos la necesidad de colocar .0 a los números para que el compilador no lo tome como enteros.

    // --------------------- string -----------------------

    assert("hola"s == "hola"s);
    assert("hola"s != "chau"s);
    assert("Hola"s + " mundo"s == "Hola mundo"s);
    assert("Hola mundo"s.length() == 10);

    // sin utilizar el namespace std, deberíamos utilizar los strings de esta forma:
    assert(std::string("hola") == std::string("hola"));

}
