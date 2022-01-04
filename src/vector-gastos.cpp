#include "gasto-diario.hpp"

void diaMasBarato(const GastoDiario regsDiarios[], const unsigned numRegs,
                  Fecha& dia, double& precioMedioMinimo) {
    GastoDiario menorPrecio = regsDiarios[0];
    
    for (int i = 1; i < numRegs; i++) {
        if (costeMedio(menorPrecio) > costeMedio(regsDiarios[i])) {
            menorPrecio = regsDiarios[i];
        }
    }
    dia.dia = menorPrecio.fecha.dia;
    precioMedioMinimo = costeMedio(menorPrecio);
}

void horaMasCara(const GastoDiario regsDiarios[], const unsigned numRegs, 
                 Fecha& dia, unsigned& hora, double& precioMaximo) {
    unsigned hora = horaMasCara(regsDiarios[0]);
    double precioMaximo = regsDiarios[0].precio[0];

    double aux; 
    for (int i = 0; i < numRegs; i++) {
        aux = regsDiarios[i].precio[horaMasCara(regsDiarios[i])];

        if (precioMaximo < aux) {
            precioMaximo = aux;
            dia.dia = regsDiarios[i].fecha.dia;
            hora = horaMasCara(regsDiarios[i]);
        }     
    }
}

double costeTerminoVaraiable(const GastoDiario regsDiarios[], 
                           const unsigned numRegs) {
    double suma = 0;
    for (unsigned i = 0; i < numRegs; i++) {
        suma += costeDiario(regsDiarios[i]);
    }
    return suma;
}

//Supongo que se refiere al coste total de todos los componentes de regsDiarios 