#include <iostream>
#include <array>
using std::array;

array<array<array<unsigned,12>,3>,4> ventas();


int main(){
    
    array<array<array<unsigned,12>,3>,4> resultados{ventas()};

    for(auto VentasPorRegion : resultados){
        
        for(auto VentasPorVendedor : VentasPorRegion){
            
            for(auto TotalVentasPorMes : VentasPorVendedor){
                std::cout << TotalVentasPorMes << '\n';
            }    
            std::cout << '\n';
        }
        std::cout << '\n';
    } 
        
    
}

array<array<array<unsigned,12>,3>,4> ventas(){
    array<array<array<unsigned,12>,3>,4> total{};
    for(unsigned region,importe,mes,vendedor; std::cin>>region>>vendedor>>mes>>importe;)
        total.at(region-1).at(vendedor-1).at(mes-1) += importe;
    return total;
}