# Algoritmo y estructura de datos

+ Curso: K1051
+ Año: 2023
+ Grupo: 12
+ Integrantes: Lucas paz - Erik Aveni  - Micaela Olivera - Ezequiel Ayala - Ignacio Herrera - Tommy Quispe  - Stete Leonel
+ Usuario:     Lucaspaz1 - ErikMercury - micaolivera     - ezequito       - iah-herrera     - Tomy-Casla    - lstete
+ Legajo:      17-333-94 - 20-338-59   - 203.908-4       - 173.294-8      - 146.479-6       - 164.825-1     - 171.465-0
+ Trabajo Práctico: Trabajo #1 - Valores y Operaciones de Tipos de Datos
+ Enunciado: Este es un trabajo no estructurado, que consiste en escribir un programa que ejemplifique el uso de los tipos de datos básicos de C++ vistos en clase: bool, char, unsigned, int, double, y string.

Créditos extra:

¿Son los enumerados en la sección anterior realmente todos los tipos que usamos en clase? Justifique

Podría agregarse el tipo de dato float

Intente probar que la suma de diez veces un décimo (0.1) es uno (1.0) ¿Qué está ocurriendo?

al probar un assert que compruebe si la suma de diez veces 0.1 da 1, falla, es decir que entiende que estas dos cosas no son iguales.
Esto sucede ya que los valores flotantes son representados mediante la norma IEEE 754, en donde tenemos un número de bits finito para representar número reales.
Para 0.1, se requiere una cantidad infinita de bits, con los cuáles no contamos. Entonces, al existir un error, este se va propagando y causando errores.

