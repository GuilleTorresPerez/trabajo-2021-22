#include "gasto-diario.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

void diaMasBarato(const GastoDiario regsDiarios[], const unsigned numRegs, Fecha& dia, double& precioMedioMinimo) {

    double precioMedio = 999.0;
    double aux;
    int index;
    
    for (unsigned i = 0; i < numRegs; i++) {
        aux = costeMedio(regsDiarios[i]);
        if (precioMedio > aux) {
            precioMedio = aux;
            index = i;
        }
    }

    dia = regsDiarios[index].fecha;
    precioMedioMinimo = precioMedio;

}

void horaMasCara(const GastoDiario regsDiarios[], const unsigned numRegs, Fecha& dia, unsigned& hora, double& precioMaximo) {

    precioMaximo = -999.0;
    double aux; 

    for (unsigned i = 0; i < numRegs; i++) {

        aux = regsDiarios[i].precio[horaMasCara(regsDiarios[i])];
        if (precioMaximo < aux) {
            precioMaximo = aux;
            dia.agno = regsDiarios[i].fecha.agno;
            dia.mes = regsDiarios[i].fecha.mes;
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