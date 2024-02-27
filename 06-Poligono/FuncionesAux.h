#ifndef FUNCIONES_AUX_INCLUIDA
#define FUNCIONES_AUX_INCLUIDA
bool AreNear(const double &, const double &, double = 0.0001);

// Para poder comparar variables del tipo double - se utiliza en SonIguales
bool AreNear(const double &a, const double &b, double tolerancia)
{
    return (a - tolerancia) <= b and b <= (a + tolerancia);
}

//todo  el contenido se va a procesar si y solo si no fue definida Funcioned_Aux_incluida
#endif