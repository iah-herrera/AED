#include <iostream>
#include <array>
using std::array;

array<array<unsigned,12>,3> ventas();


int main(){
    
    array<array<unsigned,12>, 3> resultados{ventas()};

    for(auto VentasPorVendedor : resultados){
        for(auto TotalVentasPorMes : VentasPorVendedor){

            std::cout << TotalVentasPorMes << '\n';
        }
    } 
        
    
}

array<array<unsigned,12>,3> ventas(){
    array<array<unsigned,12>,3> total{};
    for(unsigned importe,mes,vendedor; std::cin>>vendedor>>mes>>importe;)
        total.at(vendedor-1).at(mes-1) += importe;
    return total;
}