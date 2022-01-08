#include "gasto-diario.hpp"

void diaMasBarato(const GastoDiario regsDiarios[], const unsigned numRegs, Fecha& dia, double& precioMedioMinimo) {

    precioMedioMinimo = 999.0;
    double aux;
    int index;
    
    for (unsigned i = 1; i < numRegs; i++) {
        aux = costeMedio(regsDiarios[i]);
        if (precioMedioMinimo > aux) {
            precioMedioMinimo = aux;
            index = i;
        }
    }

    dia = regsDiarios[index].fecha;

}

void horaMasCara(const GastoDiario regsDiarios[], const unsigned numRegs, Fecha& dia, unsigned& hora, double& precioMaximo) {

    precioMaximo = 0;
    double aux; 

    for (unsigned i = 0; i < numRegs; i++) {

        aux = regsDiarios[i].precio[horaMasCara(regsDiarios[i])];
        if (precioMaximo < aux) {
            precioMaximo = aux;
            dia.dia = regsDiarios[i].fecha.dia;
            hora = horaMasCara(regsDiarios[i]);
        }     
    }
}

double costeTerminoVariable(const GastoDiario regsDiarios[], const unsigned numRegs) {
    double suma = 0;
    for (unsigned i = 0; i < numRegs; i++) {
        suma += costeDiario(regsDiarios[i]);
    }
    return suma;
}

//Supongo que se refiere al coste total de todos los componentes de regsDiarios 

double costeMinimoPosible(const GastoDiario regsDiarios[], const unsigned numRegs) {
    double suma = 0;
    for (unsigned i = 0; i < numRegs; i++) {
        suma += costeDiarioMinimo(regsDiarios[i]);
    }
    return suma;
}