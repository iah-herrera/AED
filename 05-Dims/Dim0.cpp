#include <iostream>
#include <array>

unsigned VentasTotal();

int main(){

    std::cout << VentasTotal() << '\n';
}
unsigned VentasTotal(){
    unsigned total{};
    for(unsigned importe; std:: cin >> importe;)
        total += importe;
    return total;
}
    