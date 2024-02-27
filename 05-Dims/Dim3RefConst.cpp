#include <iostream>
#include <array>
using std::array;

array<array<array<unsigned,12>,3>,4> GetTotalDeVentasExtraidasDeCin();//totaliza las ventas
void MostrarTotalDeVentas(array<array<array<unsigned,12>,3>,4>);

int main(){
    
    MostrarTotalDeVentas(GetTotalDeVentasExtraidasDeCin());
}

void MostrarTotalDeVentas(const array<array<array<unsigned,12>,3>,4> &resultado){
 
    for(auto VentasPorRegion : resultado){
        
        for(auto VentasPorVendedor : VentasPorRegion){
            
            for(auto TotalVentasPorMes : VentasPorVendedor)
                std::cout << TotalVentasPorMes << '\t';
            std::cout << '\n';
        }
        std::cout << '\n';
    } 
}

array<array<array<unsigned,12>,3>,4> GetTotalDeVentasExtraidasDeCin(){ 
    array<array<array<unsigned,12>,3>,4> total{};
    for(unsigned region,importe,mes,vendedor; std::cin>>region>>vendedor>>mes>>importe;)
        total.at(region-1).at(vendedor-1).at(mes-1) += importe; 
    return total;
}