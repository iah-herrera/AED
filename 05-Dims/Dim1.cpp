#include <iostream>
#include <array>


std::array<unsigned,12> ventas();

int main(){
    
    std::array<unsigned,12> resultados{ventas()};
    for(int i{};i<12;i++) //for range
        std::cout << resultados.at(i) << '\n';
    
}

std::array<unsigned,12> ventas(){
    std::array<unsigned,12> total{};
    for(unsigned importe,mes; std::cin>>importe>>mes;)
        total.at(mes-1) += importe;
    return total;
}


