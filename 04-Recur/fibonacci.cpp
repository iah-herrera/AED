# include <cassert>

/*DEFINICION MATEMATICA

fib: N --> N / fib(n)=  { n  sii  0<= n <= 1
                        { fib(n-2) + fib(n-1)  sii  n>1    e.o.c
*/


//DECLARACION
unsigned fib(unsigned n);


int main(){
    assert(fib(0)== 0);
    assert(fib(3)== 2);
    assert(fib(4)== 3);
    assert(fib(5)== 5);
    assert(fib(6)== 8);
    assert(fib(7)== 13);
    assert(fib(8)== 21);
    assert(fib(15)== 610);
}

//DEFINICION
unsigned fib(unsigned n)
{
    return n<=1 ?
    n :
    fib(n-1) + fib(n-2);
}