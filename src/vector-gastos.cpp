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
    GastoDiario mayorPrecio = regsDiarios[0];
    for (int i = 1; i < numRegs; i++) {
    }
}